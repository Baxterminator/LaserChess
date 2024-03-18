#ifndef MOVE_EVALUATION_HPP
#define MOVE_EVALUATION_HPP
#include <memory>

#include "common/game/move.hpp"

namespace laser::game {

class MoveEvaluation {
 public:
  float Evaluation;
  std::shared_ptr<Move> Move;
};
}  // namespace laser::game

#endif