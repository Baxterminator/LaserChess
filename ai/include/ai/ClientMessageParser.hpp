#ifndef CLIENT_MESSAGE_PARSER_HPP
#define CLIENT_MESSAGE_PARSER_HPP
#include <string>

typedef enum ClientMessages_tag {
    YOUR_TURN = 0,
    WON_GAME,
    LOST_GAME,
    ACTION_VALID,
    ACTION_INVALID,
    MOVE_STRING,
    INVALID_MESSAGE
} ClientMessages_t;


ClientMessages_t ClientMessageParser(std::string Message);

#endif