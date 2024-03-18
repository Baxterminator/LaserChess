#include "common/game/messages.hpp"

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

}  // namespace laser::com