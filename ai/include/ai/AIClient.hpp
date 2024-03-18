#ifndef LASER_CHESS_AI_CLIENT
#define LASER_CHESS_AI_CLIENT

#include "common/game/board.hpp"
#include "common/socket/socket.hpp"

namespace laser::ai {

enum class AIState {
  LOAD_LEVEL,  // Waiting for the level from the server
  MY_TURN,     // It's my turn to compute
  OTHER_TURN,  // It's other player turn, wait for move
  WON_LOST,    // Game is over, close connection and program
};

class LaserChessAI : public com::Socket {
 public:
  LaserChessAI(const std::string &server_ip, int server_port);

  void loop();

  bool is_game_done() const { return won || lost || error_somewhere; }

  // State computations
  /**
   * @brief Load the level description from the string.
   */
  void loadLvlDescription();

  /**
   * @brief Compute everything for our turn.
   */
  void computeTurn();

  /**
   * @brief Process the other turn to update our internal state.
   */
  void processOtherTurn();

  /**
   * @brief What to do when lost or won.
   */
  void lostOrWon();

 private:
  AIState state = AIState::LOAD_LEVEL;
  bool lost = false, won = false;
  bool error_somewhere = false;
  game::Board board;
  std::string rec_msg{""};
};

}  // namespace laser::ai

#endif
