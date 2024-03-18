#include "common/game/messages.hpp"

#include <cstring>
#include <memory>
#include <sstream>
#include <string>

#include "common/game/move.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/math/vector.hpp"

namespace laser::com {

std::string getCommand(const std::string &str) {
  // Find command edge
  bool found_start = false;
  int start = 0;
  int width = 0;
  for (unsigned long i = 0; i < str.length(); i++) {
    // Looking for command start
    if (str[i] == SOM) {
      found_start = true;
      width = 0;
      start = i + 1;
    } else if (found_start) {
      width++;
    }

    // Looking or command end;
    if (found_start && str[i] == EOM) {
      return str.substr(start, width);
    }
  }
  return MessageMap.at(Messages::INVALID_MESSAGE).first;
}

Messages getMessage(const std::string &msg) {
  auto new_msg = getCommand(msg);
  for (int i = 0; i < Messages::INVALID_MESSAGE; i++) {
    auto elem = MessageMap.at(static_cast<Messages>(i));
    if (std::strncmp(new_msg.c_str(), elem.first, elem.second)) {
      return static_cast<Messages>(i);
    }
  }
  return Messages::INVALID_MESSAGE;
}

std::string makeTurnCommand() {
  std::stringstream ss;
  ss << SOM << MessageMap.at(Messages::YOUR_TURN).first << EOM;
  return ss.str();
}

std::string makeValidAction() {
  std::stringstream ss;
  ss << SOM << MessageMap.at(Messages::ACTION_VALID).first << EOM;
  return ss.str();
}

std::string makeInvalidAction() {
  std::stringstream ss;
  ss << SOM << MessageMap.at(Messages::ACTION_INVALID).first << EOM;
  return ss.str();
}

std::string makeWon() {
  std::stringstream ss;
  ss << SOM << MessageMap.at(Messages::WON_GAME).first << EOM;
  return ss.str();
}

std::string makeLost() {
  std::stringstream ss;
  ss << SOM << MessageMap.at(Messages::LOST_GAME).first << EOM;
  return ss.str();
}

std::string makeLvlDescription(const char *level) {
  std::stringstream ss;
  ss << SOM << MessageMap.at(Messages::LVL).first << " " << level << EOM;
  return ss.str();
}

std::shared_ptr<game::Move> parseMove(const char *msg) {
  // Parse movement
  const char *p = msg;

  auto move_elem = MessageMap.at(Messages::MOVE);
  if (std::strncmp(msg, move_elem.first, move_elem.second) == 0) {
    p += move_elem.second;
    Vector start{std::stoi(p), std::stoi(p)};
    Vector to{std::stoi(p), std::stoi(p)};
    return std::make_shared<game::ShiftMove>(start, to);
  }

  auto rot_elem = MessageMap.at(Messages::ROT);
  if (std::strncmp(msg, rot_elem.first, rot_elem.second) == 0) {
    p += rot_elem.second;
    Vector start{
        std::strtol(p, (char **)&p, 10),
        std::strtol(p, (char **)&p, 10),
    };

    long rot = std::strtol(p, (char **)&p, 10);
    game::RotationDirection dir = (rot == 1) ? game::RotationDirection::LEFT : game::RotationDirection::RIGHT;
    return std::make_shared<game::RotateMove>(start, dir);
  }
}

}  // namespace laser::com