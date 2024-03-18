#include "common/game/pieces/king.hpp"

#include <utility>

#include "common/game/pieces/constants.hpp"

namespace laser::game {

std::pair<LaserInteraction, Vector> King::GetLaserInteraction(Vector incomingLaser) const {
  return std::make_pair(LaserInteraction::HIT, ZERO_VECTOR);
}

Orientation King::LaserDirectionToOrientation(Vector laserDirection) const { return Orientation::NO_ORIENTATION; }

Vector King::GetDeflectedLaserDirection(Vector laserDirection) const { return ZERO_VECTOR; }

int King::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const { return 0; }
}  // namespace laser::game
