#ifndef MOVE_HPP
#define MOVE_HPP

#include "common/game/board.hpp"
#include "common/game/pieces/piece.hpp"
#include "common/math/vector.hpp"

namespace laser::game {

struct Move {
  Vector StartPosition;
  Vector EndPosition;

  Move(Vector pos) : StartPosition(pos), EndPosition(ZERO_VECTOR) {}
  Move(Vector startPosition, Vector endPosition) : StartPosition(startPosition), EndPosition(endPosition) {}
  virtual ~Move() = default;
  virtual bool LegalMove(const Board_t& board, PieceColor playerColor) const = 0;
  virtual void ApplyMove(Board& board) = 0;
};

// Classic shift. Move from one square to the other
struct ShiftMove : public Move {
  ShiftMove(Vector startPosition, Vector endPosition) : Move(startPosition, endPosition) {}
  bool LegalMove(const Board_t& board, PieceColor playerColor) const override;
  void ApplyMove(Board& board) override;
};

// Switches positions with the piece (Only switches can perform this move)
struct SwitchMove : public Move {
  SwitchMove(Vector startPosition, Vector endPosition) : Move(startPosition, endPosition) {}
  bool LegalMove(const Board_t& board, PieceColor playerColor) const override;
  void ApplyMove(Board& board) override;
};

struct RotateMove : public Move {
  RotationDirection direction;

  RotateMove(Vector piecePosition, RotationDirection rotDirection) : Move(piecePosition), direction(rotDirection) {}
  RotateMove() : Move(ZERO_VECTOR) {}
  bool LegalMove(const Board_t& board, PieceColor playerColor) const override { return true; };
  void ApplyMove(Board& board) {}
};

}  // namespace laser::game

#endif