#include "../include/response_gen.h"
#include "../include/requests_parser.h"

namespace fs = std::filesystem;
std::map<int, std::string> statusToText = {
    // Success
    {200, "OK"},
    {201, "Created"},
    {204, "No Content"},
    // Redirects
    {301, "Moved Permanently"},
    {302, "Found"},
    {304, "Not Modified"},
    // Client Errors
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {408, "Request Timeout"},
    {409, "Conflict"},
    {429, "Too Many Requests"},
    // Server Errors
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"},
    {504, "Gateway Timeout"}
};
std::string body_generate(std::string text){
    return
        "<html>"
        "<head><title>" + text + "</title></head>"
        "<body>"
        "<h1>" + text + "</h1>"
        "</body>"
        "</html>";
}
std::string get_file_path(Message* request){
    // GET /
    if (request->file == "/")
        return "../public/index.html";
    return "../public" + request->file;
}

bool exists(Message* request){
    std::string path = get_file_path(request);
    return fs::exists(path) &&
           fs::is_regular_file(path);
}
std::string read_file(const std::string& path){
    std::ifstream file(path);
    if (!file.is_open())
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
std::string generate_response(Message* request){
    int status_code;
    std::string body;
    if (exists(request)){
        status_code = 200;
        std::string path = get_file_path(request);
        body = read_file(path);
        // file exists but could not be read
        if (body.empty()){
            status_code = 500;
            body = body_generate("500 Internal Server Error");
        }
    }
    else{
        status_code = 404;
        body = body_generate("404 Not Found");
    }
    std::string response;
    response += "HTTP/1.1 ";
    response += std::to_string(status_code);
    response += " ";
    response += statusToText[status_code];
    response += "\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Content-Length: ";
    response += std::to_string(body.length());
    response += "\r\n";
    response += "Connection: close\r\n";
    response += "\r\n";
    response += body;
    return response;
}