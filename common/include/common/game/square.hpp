#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <memory>

#include "common/game/pieces/piece.hpp"
#include "common/math/vector.hpp"

namespace laser::game {
class Square {
 public:
  Vector Position;
  std::shared_ptr<Piece> Piece;
  PieceColor ReservedSquare;  // Some squares are reserved for red/blue

  Square() : Position({-1, -1}), Piece(nullptr), ReservedSquare(PieceColor::NONE){};

  bool operator==(const Square& otherSquare) const { return this->Position == otherSquare.Position; }

  struct HashFunction {
    size_t operator()(const Square& square) const {
      size_t rowHash = std::hash<int>{}(square.Position.y);
      size_t colHash = std::hash<int>{}(square.Position.x);
      return rowHash * 37 + colHash;
    }
  };
};
}  // namespace laser::game

#endif