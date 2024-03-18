#ifndef MOVE_EVALUATION_HPP
#define MOVE_EVALUATION_HPP
#include <memory>
#include "ai/Move.hpp"


class MoveEvaluation {
public:
    float Evaluation;
    std::shared_ptr<Move> Move;
};

#endif