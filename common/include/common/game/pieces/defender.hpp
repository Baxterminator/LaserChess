#ifndef LASER_CHESS_DEFENDER_HPP
#define LASER_CHESS_DEFENDER_HPP

#include "common/game/pieces/piece.hpp"

namespace laser::game {

class Defender : public Piece {
 public:
  Defender(PieceColor pieceColor, Orientation orientation) : Piece(PieceType::DEFENDER, pieceColor, orientation, 4) {
    this->display_char = (pieceColor == PieceColor::BLUE) ? 'B' : 'b';
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