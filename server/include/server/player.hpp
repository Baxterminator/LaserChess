#ifndef LASER_CHESS_PLAYER
#define LASER_CHESS_PLAYER

#include "common/game/messages.hpp"
#include "common/game/move.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/socket/socket.hpp"

namespace laser::server {

struct Player : public com::Socket {
  static constexpr const char* PLAYER_1{"Player 1"};
  static constexpr const char* PLAYER_2{"Player 2"};

  Player() : com::Socket() {}
  Player(const char* name, game::PieceColor color, com::Socket sk);

  void sendLevel(const char* lvl) { send_data(com::makeLvlDescription(lvl)); }
  void sendTurnStart() { send_data(com::makeTurnCommand()); }
  void sendMoveInvalid() { send_data(com::makeInvalidAction()); }
  void sendMoveValid() { send_data(com::makeValidAction()); }
  void sendWon() { send_data(com::makeWon()); }
  void sendLost() { send_data(com::makeLost()); }

  std::shared_ptr<game::Move> getMovement();

 public:
  const char* name;
  game::PieceColor color;
  std::string last_msg{""};
  std::shared_ptr<game::Move> last_move;
};

}  // namespace laser::server

#endif
