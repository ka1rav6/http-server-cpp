
#ifndef REQUESTS_PARSER
#define REQUESTS_PARSER
#include <string>
#pragma once

struct Message{
    std::string type;
    std::string file;
};

Message* parse(std::string msg);
void destroy(Message* msg);

#endif
