#ifndef LASER_CHESS_SERVER
#define LASER_CHESS_SERVER

#include <memory>

#include "common/game/board.hpp"
#include "common/socket/server.hpp"
#include "common/socket/socket.hpp"
#include "server/player.hpp"

namespace laser::server {

class GameServer : public com::SocketServer {
 public:
  GameServer(int);

  /**
   * @brief Wait for two players to connect.
   */
  void waitForPlayers();

  /**
   * @brief Load the level for the server.
   */
  void loadLevel(const char*);

  /**
   * @brief Return whether the game is over or not
   */
  inline bool isGameDone() { return done; }

  /**
   * @brief Compute the next server loop.
   */
  void loop();

 public:
  const char* lvl{""};
  game::Board board;
  bool round_player1 = true;
  std::shared_ptr<Player> player1, player2;
  bool done = false;
};

}  // namespace laser::server

#endif