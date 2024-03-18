#include "server/server.hpp"

#include "common/socket/server.hpp"

namespace laser::server {

GameServer::GameServer(int port) : com::SocketServer(port) {}

void GameServer::wait_for_players() {
  std::cout << "Waiting for Player 1" << std::endl;
  player1 = wait_for_client();

  std::cout << "Waiting for Player 1" << std::endl;
  player2 = wait_for_client();
}

void GameServer::loop() {}

}  // namespace laser::server