#include "../include/requests_parser.h"
#include <sstream>

Message* parse(const std::string& msg){

    Message* final = new Message;
    std::stringstream ss(msg);
    ss >> final->type;
    ss >> final->file;
    std::string line;
    std::getline(ss, line);
    while (std::getline(ss, line)){
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.find("Host: ") == 0){
            final->host = line.substr(6);
        }
        else if (line.find("Connection: ") == 0){
            final->Connection = line.substr(12);
        }
    }
    return final;
}

void destroy(Message* msg){
    delete msg;
}