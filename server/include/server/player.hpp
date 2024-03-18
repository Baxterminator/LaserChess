#ifndef LASER_CHESS_PLAYER
#define LASER_CHESS_PLAYER

#include "common/game/messages.hpp"
#include "common/socket/socket.hpp"

namespace laser::server {

struct Player : public com::Socket {
  static constexpr const char* PLAYER_1{"Player 1"};
  static constexpr const char* PLAYER_2{"Player 2"};

  Player() : com::Socket() {}
  Player(const char* name, com::Socket sk);

  void sendTurnStart() { send_data(com::makeTurnCommand()); }

 public:
  const char* name;
};

}  // namespace laser::server

#endif
