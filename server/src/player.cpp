#include "server/player.hpp"

#include "common/socket/socket.hpp"

namespace laser::server {

Player::Player(const char* _name, com::Socket sk) : com::Socket(sk), name(_name) {}

}  // namespace laser::server