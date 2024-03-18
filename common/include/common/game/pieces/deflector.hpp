#ifndef DEFLECTOR_HPP
#define DEFLECTOR_HPP

#include "common/game/pieces/piece.hpp"

namespace laser::game {

class Deflector : public Piece {
 public:
  Deflector(PieceColor pieceColor, Orientation orientation) : Piece(PieceType::DEFLECTOR, pieceColor, orientation, 4) {
    this->display_char = (pieceColor == PieceColor::BLUE) ? 'D' : 'd';
    this->switch_allowed = true;
  }

  std::pair<LaserInteraction, Vector> GetLaserInteraction(Vector incomingLaser) const override;
  Orientation LaserDirectionToOrientation(Vector laserDirection) const override;
  Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
  int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;

  // void RotateLeft();
  // void RotateRight();
};

}  // namespace laser::game

#endif