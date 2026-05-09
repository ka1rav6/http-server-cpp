// IO 
#include <fstream>
#include <iostream>
#include <cerrno>

// for socket
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

// Definitions
#define BUF_SIZE 4096 // 2^12

//IO functions

void log(std::string msg){
    using namespace std;
    ofstream logger("error_logs.txt");
    logger << msg << std::endl;
    logger << "Error Code: " << errno << endl;
    cout << "Error logged! \n";
}

class Server{
    private:
        int fd;
        struct sockaddr_in addr;
        void createSocket(){
            this->fd = socket(AF_INET, SOCK_STREAM, 0);
            if (this->fd == -1){
                log("Socket Initialzation Failed");
            }
        }
        void configureSocket(){
            this->addr.sin_family = AF_INET;
            this->addr.sin_port = htons(8080);
            this->addr.sin_addr.s_addr = INADDR_ANY;
        }
        void bindSocket(){
            if (::bind(this->fd, 
                (const struct sockaddr *)(&this->addr),
                sizeof(this->addr)))
                    log("Binding Failure");
        }
    public:
        int get_fd(){
            return this->fd;
        }
        struct sockaddr_in get_addr(){
            return this->addr;
        }
        void init(){
            this->createSocket();
            this->configureSocket();
            this->bindSocket();
        }
        void listen(int backlog){
            if (::listen(this->fd, backlog) <0)
                log("Unable to Listen");
        }
        void read(int client_fd, char* buffer){
            int bytes = ::read(client_fd, buffer, BUF_SIZE - 1);
            if (bytes > 0){
                // The HTTP REQUEST COMES HERE
                buffer[bytes] = '\0';
                std::cout << "Client says: " << buffer << '\n';
                send(client_fd, "OK", 2, 0);
            }
            else if (bytes == 0)
                log("Client has been disconnected");
            else
                log("Read Failed");
        }
};

class Client{
    private:
        int fd;
        struct sockaddr_in addr;
    public:
        socklen_t len = sizeof(this->addr);
        int get_fd(){
            return this->fd;
        }
        struct sockaddr_in get_addr(){
            return this->addr;
        }
        void accept(int server_fd){
            this->fd = ::accept(server_fd, reinterpret_cast<struct sockaddr*> (&this->addr), 
                    &(this->len));
            if (this->fd < 0)
                log("Accepting Failed");
        }
};

int main(void){
    Server s;
    s.init();
    s.listen(5);
    std::cout << "Server is listening on port 8080....\n";
    Client c;
    char* buffer = new char[BUF_SIZE];

    while (true){
        c.accept(s.get_fd());
        s.read(c.get_fd(), buffer);
        
        close(c.get_fd());
    }
    delete[] buffer;
    close(s.get_fd());
    return 0;
}
