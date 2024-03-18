#include "ai/ClientMessageParser.hpp"

const std::string CLIENTMESSAGES[] =
{
    ";yourturn\n",
    ";won\n",
    ";lost\n",
    ";action valid\n",
    ";action invalid\n",
};

ClientMessages_t ClientMessageParser(std::string Message)
{
    ClientMessages_t clientMessage = INVALID_MESSAGE;
    if (Message == CLIENTMESSAGES[YOUR_TURN]) 
    {
        clientMessage = YOUR_TURN;
    }

    else if (Message == CLIENTMESSAGES[WON_GAME])
    {
        clientMessage = WON_GAME;
    }

    else if (Message == CLIENTMESSAGES[LOST_GAME])
    {
        clientMessage = LOST_GAME;
    }

    else if (Message == CLIENTMESSAGES[ACTION_VALID])
    {
        clientMessage = ACTION_VALID;
    }

    else if (Message == CLIENTMESSAGES[ACTION_INVALID])
    {
        clientMessage = ACTION_INVALID;
    }

    return clientMessage;
}