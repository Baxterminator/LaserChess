#include "server/server.hpp"

#include "common/game/messages.hpp"
#include "common/socket/server.hpp"

namespace laser::server {

GameServer::GameServer(int port) : com::SocketServer(port) {}

void GameServer::wait_for_players() {
  std::cout << "Waiting for Player 1" << std::endl;
  player1 = Player(Player::PLAYER_1, wait_for_client());

  std::cout << "Waiting for Player 1" << std::endl;
  player2 = Player(Player::PLAYER_2, wait_for_client());
}

void GameServer::loop() {
  // Get player turn
  auto& player = (round_player1) ? player1 : player2;

  // Send turn notification
  std::cout << "> " << player.name << " turn";
  player.send_data(com::makeTurnCommand());

  // Wait for his actions

  // TODO: Test if won

  // Prepare for next loop
  round_player1 = !round_player1;
}

}  // namespace laser::server