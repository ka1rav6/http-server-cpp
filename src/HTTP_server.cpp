// IO
#include <fstream>
#include <iostream>
#include <cerrno>
#include <thread>

// sockets
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

// CUSTOM HEADERS
#include "../include/requests_parser.h"
#include "../include/response_gen.h"

#define BUF_SIZE 4096
void log(const std::string& msg){
    std::ofstream logger("error_logs.txt", std::ios::app);
    logger << msg << '\n';
    logger << "Error Code: " << errno << '\n';
    logger << "-------------------\n";
    std::cout << "Error logged!\n";
}

class Server{
    private:
        int fd;
        struct sockaddr_in addr;

        void createSocket(){
            this->fd = socket(AF_INET, SOCK_STREAM, 0);
            if (this->fd < 0){
                log("Socket Creation Failed");
                exit(EXIT_FAILURE);
            }
        }
        void configureSocket(){
            memset(&this->addr, 0, sizeof(this->addr));
            this->addr.sin_family = AF_INET;
            this->addr.sin_port = htons(8080);
            this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
            int opt = 1;
            if (
                setsockopt(
                    this->fd,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    &opt,
                    sizeof(opt)
                ) < 0
            ){
                log("setsockopt Failed");
                exit(EXIT_FAILURE);
            }
        }
        void bindSocket(){
            if (
                ::bind(
                    this->fd,
                    reinterpret_cast<sockaddr*>(&this->addr),
                    sizeof(this->addr)
                ) < 0
            ){
                log("Bind Failed");
                exit(EXIT_FAILURE);
            }
        }
    public:
        void init(){
            this->createSocket();
            this->configureSocket();
            this->bindSocket();
        }
        void listen(int backlog){
            if (::listen(this->fd, backlog) < 0){
                log("Listen Failed");
                exit(EXIT_FAILURE);
            }
        }
        int get_fd(){
            return this->fd;
        }
    void handleClient(int client_fd, char* buffer){
    ssize_t bytes = recv(
        client_fd,
        buffer,
        BUF_SIZE - 1,
        0
    );
    if (bytes <= 0){
        std::cout << "recv failed\n";
        return;
    }
    buffer[bytes] = '\0';
    std::cout << "REQUEST:\n";
    std::cout << buffer << '\n';
    Message* client_request = parse(buffer);
    if (!client_request){
        std::cout << "Request Parsing Failiure\n";
        return;
    }
    std::string response= 
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 7\r\n"
        "Connection: close\r\n"
        "\r\n"
        "DEFAULT";
    if (client_request->type == "GET"){
        response = generate_response(client_request);
    }
    ssize_t sent = send(
        client_fd,
        response.c_str(),
        response.size(),
        0
    );
    std::cout << "BYTES SENT: "
              << sent
              << '\n';
    delete client_request;
}
};

int main(){
    Server server;
    server.init();
    server.listen(5);
    std::cout << "Server listening on port 8080...\n";
    char* buffer = new char[BUF_SIZE];
    while (true) {
        int client_fd = accept(
            server.get_fd(),
            nullptr,
            nullptr
        );
        if (client_fd < 0) {
            log("Accept Failed");
            continue;
        }
        std::thread([client_fd]() {
            char buffer[BUF_SIZE];
            ssize_t bytes = recv(client_fd, buffer, BUF_SIZE - 1, 0);
            if (bytes <= 0) {
                std::cout << "recv failed\n";
                close(client_fd);
                return;
            }
            buffer[bytes] = '\0';
            std::cout << "REQUEST:\n" << buffer << '\n';
            Message* client_request = parse(buffer);
            std::string response =
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 7\r\n"
                "Connection: close\r\n"
                "\r\n"
                "DEFAULT";
            if (client_request && client_request->type == "GET") {
                response = generate_response(client_request);
            }
            send(client_fd, response.c_str(), response.size(), 0);
            destroy(client_request);
            close(client_fd);
        }).detach();
    }
    delete[] buffer;
    close(server.get_fd());
    return 0;
}

