#include "server/server.hpp"

#include <cstring>

#include "common/game/messages.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/socket/errors.hpp"
#include "common/socket/server.hpp"
#include "levels/level1.hpp"

namespace laser::server {

GameServer::GameServer(int port) : com::SocketServer(port) {}

void GameServer::loadLevel(const char* level_name) {
  if (strcmp(level_name, "level1") == 0) {
    lvl = level::LEVEL1;
  }
  board.loadFromString(lvl);
}

void GameServer::waitForPlayers() {
  std::cout << "Waiting for Player 1" << std::endl;
  player1 = std::make_shared<Player>(Player::PLAYER_1, game::PieceColor::BLUE, wait_for_client_raw());
  player1->sendLevel(lvl, true);

  std::cout << "Waiting for Player 2" << std::endl;
  player2 = std::make_shared<Player>(Player::PLAYER_2, game::PieceColor::RED, wait_for_client_raw());
  player2->sendLevel(lvl, false);
}

void GameServer::loop() {
  std::cout << "Beginning loop" << std::endl;
  // Get player turn
  auto player = (round_player1) ? player1 : player2;
  auto other = (round_player1) ? player2 : player1;

  // Send turn notification
  std::cout << "> " << player->name << " turn" << std::endl;
  if (auto error = player->send_data(com::makeTurnCommand()); error != com::SocketErrors::NO_ERROR) {
    std::cout << "Socket error " << com::error2String(error) << " - " << strerror(errno) << "! Stopping client..."
              << std::endl;
  };
  if (auto error = player->send_data(com::makeTurnCommand()); error != com::SocketErrors::NO_ERROR) {
    std::cout << "Socket error " << com::error2String(error) << " - " << strerror(errno) << "! Stopping client..."
              << std::endl;
  };

  bool valid = false;

  // Wait for a valid action
  while (!valid) {
    auto move = player->getMovement();

    // Check his action
    if (move->LegalMove(board.board, player->color)) {
      move->ApplyMove(board);
      player->sendMoveValid();
      other->send_data(player->last_msg);  // Send the data to the other so it can update its map
    } else
      player->sendMoveInvalid();
  }

  // Test if won (end the game)
  if (auto c = board.hasSomeoneWon(); c != game::PieceColor::NONE) {
    done = true;
    if (c == player1->color) {
      player->sendWon();
      other->sendLost();
    } else {
      player->sendLost();
      other->sendWon();
    }
  }

  // Prepare for next loop
  round_player1 = !round_player1;
}

}  // namespace laser::server