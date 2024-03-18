#ifndef LASER_CHESS_PIECE_HPP
#define LASER_CHESS_PIECE_HPP

#include <utility>

#include "common/game/pieces/constants.hpp"
#include "common/math/vector.hpp"

namespace laser::game {

class Piece {
 public:
  Piece(PieceType _type, PieceColor _color, Orientation _orientation, int _n_orients)
      : type(_type), color(_color), orient(_orientation), n_orients(_n_orients) {}

  PieceColor GetPieceColor() { return this->color; }

  Orientation GetOrientation() { return this->orient; }

  int GetNumOrientations() { return this->n_orients; }

  PieceType GetPieceType() { return this->type; }

  bool GetSwitchPermission() { return this->switch_allowed; }
  virtual ~Piece() = default;

  virtual std::pair<LaserInteraction, Vector> GetLaserInteraction(Vector incomingLaser) const = 0;
  virtual Orientation LaserDirectionToOrientation(Vector laserDirection) const = 0;
  virtual Vector GetDeflectedLaserDirection(Vector laserDirection) const = 0;
  virtual int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const = 0;

 protected:
  PieceType type;
  PieceColor color;
  Orientation orient;
  int n_orients;
  char display_char;
  bool switch_allowed;
};

}  // namespace laser::game

#endif