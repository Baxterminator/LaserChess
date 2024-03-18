#ifndef KING_HPP
#define KING_HPP

#include "common/game/pieces/constants.hpp"
#include "common/game/pieces/piece.hpp"

namespace laser::game {

class King : public Piece {
 public:
  King(PieceColor pieceColor, Orientation orientation) : Piece(PieceType::KING, pieceColor, orientation, 1) {
    this->display_char = (pieceColor == PieceColor::BLUE) ? 'K' : 'k';
    this->switch_allowed = false;
  };

  std::pair<LaserInteraction, Vector> GetLaserInteraction(Vector incomingLaser) const override;
  Orientation LaserDirectionToOrientation(Vector laserDirection) const override;
  Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
  int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;
};
}  // namespace laser::game

#endif