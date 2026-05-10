
#ifndef REQUESTS_PARSER
#define REQUESTS_PARSER
#include <string>
#pragma once

struct Message{
    std::string type;
    std::string file;
    std::string host;
    std::string Connection;
};

Message* parse(const std::string& msg);
void destroy(Message* msg);

#endif
