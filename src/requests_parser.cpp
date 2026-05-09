#include "../include/requests_parser.h"

Message* parse(std::string msg){
    Message* final = new Message;
    final->type = "";
    final->file = "";
    int i =0;
    while (msg.at(i) != ' ' && i < msg.size())
        final->type += msg.at(i++);
    i++;
    while (msg.at(i) != ' ' && i < msg.size())
        final->file += msg.at(i);
    // Nothing else is needed to be noted but can be stored using the same method
    return final;
};
void destroy(Message* msg){
    delete msg;
}
