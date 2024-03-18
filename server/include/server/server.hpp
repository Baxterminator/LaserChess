#ifndef LASER_CHESS_SERVER
#define LASER_CHESS_SERVER

#include <memory>

#include "common/socket/server.hpp"
#include "common/socket/socket.hpp"

namespace laser::server {

class GameServer : private com::SocketServer {
 public:
  GameServer(int);

  /**
   * @brief Wait for two players to connect.
   */
  void wait_for_players();

  /**
   * @brief Return whether the game is over or not
   */
  inline bool is_game_done() { return done; }

  /**
   * @brief Compute the next server loop.
   */
  void loop();

 private:
  com::Socket player1, player2;
  bool done = false;
};

}  // namespace laser::server

#endif