#include <map>
#include <string>

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



