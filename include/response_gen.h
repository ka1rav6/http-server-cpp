#ifndef RESPONSE_GEN
#define RESPONSE_GEN

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "requests_parser.h"


bool exists(Message* request);
std::string generate_response(Message* request);
std::string body_generate(std::string main_text);
std::string get_file_path(Message* request);
std::string read_file(const std::string& path);



#endif
