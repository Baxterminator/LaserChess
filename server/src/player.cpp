#include "server/player.hpp"

#include <cstring>

#include "common/game/messages.hpp"
#include "common/socket/errors.hpp"
#include "common/socket/socket.hpp"

namespace laser::server {

Player::Player(const char* _name, game::PieceColor color, com::Socket sk)
    : com::Socket(sk), name(_name), color(color) {}

std::shared_ptr<game::Move> Player::getMovement() {
  // Receive data
  if (auto error = receive_data(last_msg); error != com::SocketErrors::NO_ERROR) {
    return nullptr;
  }

  // Parse data
  return com::parseMove(last_msg.c_str());
}

}  // namespace laser::server