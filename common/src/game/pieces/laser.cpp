#include "common/game/pieces/laser.hpp"

#include <utility>

#include "common/game/pieces/constants.hpp"

namespace laser::game {

std::pair<LaserInteraction, Vector> Laser::GetLaserInteraction(Vector incomingLaser) const {
  return std::make_pair(LaserInteraction::BLOCK, ZERO_VECTOR);
}

Orientation Laser::LaserDirectionToOrientation(Vector laserDirection) const { return Orientation::NO_ORIENTATION; }

Vector Laser::GetDeflectedLaserDirection(Vector laserDirection) const { return ZERO_VECTOR; }

int Laser::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const { return 0; }

}  // namespace laser::game
