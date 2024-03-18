
#include "common/game/pieces/switch.hpp"

#include <utility>

#include "common/game/pieces/constants.hpp"

namespace laser::game {

Orientation Switch::LaserDirectionToOrientation(Vector laserDirection) const {
  Orientation orientation = Orientation::NO_ORIENTATION;
  if (laserDirection == UP_VECTOR) {
    orientation = Orientation::NORTH_WEST;
  }

  else if (laserDirection == DOWN_VECTOR) {
    orientation = Orientation::NORTH_EAST;
  }

  else if (laserDirection == RIGHT_VECTOR) {
    orientation = Orientation::SOUTH_EAST;
  }

  else if (laserDirection == LEFT_VECTOR) {
    orientation = Orientation::NORTH_WEST;
  }

  return orientation;
}

std::pair<LaserInteraction, Vector> Switch::GetLaserInteraction(Vector incomingLaser) const {
  Orientation laserOrientation = this->LaserDirectionToOrientation(incomingLaser);
  Vector newLaserDirection = this->GetDeflectedLaserDirection(incomingLaser);
  return std::make_pair(LaserInteraction::DEFLECT, newLaserDirection);
}

Vector Switch::GetDeflectedLaserDirection(Vector laserDirection) const {
  switch (this->orient) {
    case Orientation::NORTH_EAST: {
      if (laserDirection == DOWN_VECTOR) {
        return RIGHT_VECTOR;
      }

      else if (laserDirection == LEFT_VECTOR) {
        return DOWN_VECTOR;
      }
      break;
    }

    case Orientation::NORTH_WEST: {
      if (laserDirection == UP_VECTOR) {
        return LEFT_VECTOR;
      }

      else if (laserDirection == LEFT_VECTOR) {
        return UP_VECTOR;
      }
      break;
    }

    case Orientation::SOUTH_WEST:
    case Orientation::SOUTH_EAST:
    default: {
      return ZERO_VECTOR;
      break;
    }
  }
}

int Switch::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const {
  return 1500 / (piecePosition - opKingPosition).CalculateManHatDistance();
}
}  // namespace laser::game