#ifndef LASER_CHESS_MESSAGES
#define LASER_CHESS_MESSAGES

#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "common/game/move.hpp"

namespace laser::com {

constexpr const char SOM{';'};   //< Start of message
constexpr const char EOM{'\n'};  //< End of message

enum Messages {
  // Level message
  LVL = 0,
  LVL_ERROR,
  ACK,

  // Turn
  YOUR_TURN,
  ACTION_VALID,
  ACTION_INVALID,

  MOVE,
  ROT,

  // Results
  WON_GAME,
  LOST_GAME,

  // Others
  INVALID_MESSAGE,
};

inline static std::unordered_map<Messages, std::pair<const char *, unsigned char>> MessageMap{
    {Messages::LVL, {"lvl", 3}},
    {Messages::LVL_ERROR, {"lvlerror", 8}},
    {Messages::ACK, {"ack", 3}},
    {Messages::YOUR_TURN, {"yourturn", 8}},
    {Messages::WON_GAME, {"won", 3}},
    {Messages::LOST_GAME, {"lost", 4}},
    {Messages::INVALID_MESSAGE, {"invalid", 7}},
};

std::string getCommand(const std::string &str);

Messages getMessage(const std::string &msg);

std::string makeTurnCommand();
std::string makeValidAction();
std::string makeInvalidAction();
std::string makeWon();
std::string makeLost();
std::string makeLvlDescription(const char *);

std::shared_ptr<game::Move> parseMove(const char *);

}  // namespace laser::com

#endif