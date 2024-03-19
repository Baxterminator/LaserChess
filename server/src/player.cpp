#include "server/player.hpp"

#include <cstring>

#include "common/game/messages.hpp"
#include "common/socket/errors.hpp"
#include "common/socket/socket.hpp"

namespace laser::server {

Player::Player(std::string _name, game::PieceColor color, SOCKET sk) : com::Socket(sk), name(_name), color(color) {}

std::shared_ptr<game::Move> Player::getMovement() {
  // Receive data
  last_msg = "";
  do {
    if (auto error = receive_data(last_msg); error != com::SocketErrors::NO_ERROR) {
      return nullptr;
    }
  } while (last_msg.length() == 0);

  // Parse data
  return com::parseMove(last_msg.c_str());
}

}  // namespace laser::server