#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "common/game/pieces/piece.hpp"

namespace laser::game {

class Switch : public Piece {
 public:
  Switch(PieceColor pieceColor, Orientation orientation) : Piece(PieceType::SWITCH, pieceColor, orientation, 2) {
    this->display_char = (pieceColor == PieceColor::BLUE) ? 'S' : 's';
    this->switch_allowed = false;
  }

  std::pair<LaserInteraction, Vector> GetLaserInteraction(Vector incomingLaser) const override;
  Orientation LaserDirectionToOrientation(Vector laserDirection) const override;
  Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
  int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;
};

}  // namespace laser::game

#endif