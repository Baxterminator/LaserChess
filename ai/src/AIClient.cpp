#include "ai/AIClient.hpp"

#include <cerrno>
#include <cstring>
#include <iostream>

#include "common/game/messages.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/socket/errors.hpp"
#include "common/socket/socket.hpp"

namespace laser::ai {

LaserChessAI::LaserChessAI(const std::string& server_ip, int server_port) : com::Socket(server_ip, server_port) {}

void LaserChessAI::loop() {
  std::cout << "Loop" << std::endl;
  // Receive data
  if (auto error = receive_data(rec_msg); error != com::SocketErrors::NO_ERROR) {
    std::cout << "Socket error " << com::error2String(error) << " - " << strerror(errno) << "! Stopping client..."
              << std::endl;
    error_somewhere = true;
    return;
  }
  if (rec_msg.length() == 0) {
    std::cout << rec_msg << std::endl;
    return;
  }

  // If won or lost, stop the AI
  won = com::isWon(rec_msg);
  lost = com::isLost(rec_msg);
  if (won || lost) state = AIState::WON_LOST;

  // Act
  switch (state) {
    case AIState::LOAD_LEVEL:
      loadLvlDescription();
      break;
    case AIState::MY_TURN:
      computeTurn();
      break;
    case AIState::OTHER_TURN:
      processOtherTurn();
      break;
    case AIState::WON_LOST:
      break;
  }
}

void LaserChessAI::loadLvlDescription() {
  if (!com::isLvlDescription(rec_msg)) {
    std::cout << "Got un unexpected message \"" << rec_msg << "\"" << std::endl;
    error_somewhere = true;
    return;
  };

  std::cout << "Parsing level" << std::endl;

  const char* p = rec_msg.c_str();
  p += com::MessageMap.at(com::Messages::LVL).second + 1;

  bool start_now = std::strtol(p, (char**)&p, 10) == 1;
  board.loadFromString(p);

  state = (start_now) ? AIState::MY_TURN : AIState::OTHER_TURN;
  if (!start_now)
    std::cout << "Waiting for other player action ..." << std::endl;
  else
    std::cout << "Waiting for server to launch turn ..." << std::endl;
}

void LaserChessAI::computeTurn() {
  // Test for message validity
  if (!com::isMyTurn(rec_msg)) {
    std::cout << "Got un unexpected message \"" << rec_msg << "\"" << std::endl;
    error_somewhere = true;
    return;
  }

  std::cout << "Compute action turn" << std::endl;

  // Send computed action
  std::string moveString = FindBestMove(game::PieceColor::BLUE, board);
  if (auto error = send_data(moveString); error != laser::com::SocketErrors::NO_ERROR) {
    std::cout << "Socket error " << com::error2String(error) << "! Stopping client..." << std::endl;
    error_somewhere = true;
    return;
  }

  // Wait for server validation
  receive_data(rec_msg);
  if (com::isInvalidAction(rec_msg)) {
    std::cout << "Using an invalid action? Stopping the client ..." << std::endl;
  } else if (com::isValidAction(rec_msg)) {
    std::cout << "Got action acknolegment!" << std::endl;
    std::cout << "Waiting for other player action ..." << std::endl;
    state = AIState::OTHER_TURN;
  } else {
    std::cout << "Got a unexpected message: \"" << rec_msg << "\"" << std::endl;
    error_somewhere = true;
    return;
  }
}

void LaserChessAI::processOtherTurn() {
  // Test for message validity
  if (!com::isMove(rec_msg) && !com::isRot(rec_msg)) {
    std::cout << "Got un unexpected message \"" << rec_msg << "\"" << std::endl;
    error_somewhere = true;
    return;
  }

  // Apply move
  auto move = com::parseMove(rec_msg.c_str());
  move->ApplyMove(board);

  state = AIState::MY_TURN;
}

void LaserChessAI::lostOrWon() {
  if (won)
    std::cout << "This AI has won!" << std::endl;
  else if (lost)
    std::cout << "The other player has won!" << std::endl;
  else
    std::cout << "What's happing? In winning or losing state without winning or losing :/";
}

}  // namespace laser::ai