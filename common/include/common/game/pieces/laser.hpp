#ifndef LASER_HPP
#define LASER_HPP

#include "common/game/pieces/constants.hpp"
#include "common/game/pieces/piece.hpp"

namespace laser::game {

class Laser : public Piece {
 public:
  Laser(PieceColor pieceColor, Orientation orientation) : Piece(PieceType::LASER, pieceColor, orientation, 1) {
    this->display_char = (pieceColor == PieceColor::BLUE) ? 'L' : 'l';
  };

  std::pair<LaserInteraction, Vector> GetLaserInteraction(Vector incomingLaser) const override;
  Orientation LaserDirectionToOrientation(Vector laserDirection) const override;
  Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
  int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;
};
}  // namespace laser::game

#endif