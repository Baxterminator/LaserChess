#include "common/game/pieces/deflector.hpp"

#include <utility>

#include "common/game/pieces/constants.hpp"

namespace laser::game {

Orientation Deflector::LaserDirectionToOrientation(Vector laserDirection) const {
  Orientation orientation = Orientation::NO_ORIENTATION;
  if (laserDirection == UP_VECTOR) {
    orientation = Orientation::SOUTH_WEST;
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

std::pair<LaserInteraction, Vector> Deflector::GetLaserInteraction(Vector incomingLaser) const {
  Orientation laserOrientation = this->LaserDirectionToOrientation(incomingLaser);
  Orientation otherAcceptedOrientation = Orientation::NO_ORIENTATION;
  switch (laserOrientation) {
    case Orientation::SOUTH_WEST: {
      otherAcceptedOrientation = Orientation::SOUTH_EAST;
      break;
    }

    case Orientation::NORTH_EAST: {
      otherAcceptedOrientation = Orientation::NORTH_WEST;
      break;
    }

    case Orientation::SOUTH_EAST: {
      otherAcceptedOrientation = Orientation::SOUTH_WEST;
      break;
    }

    case Orientation::NORTH_WEST: {
      otherAcceptedOrientation = Orientation::NORTH_EAST;
      break;
    }

    default: {
      // should never happen
      break;
    }
  }

  if (laserOrientation == this->orient || laserOrientation == otherAcceptedOrientation) {
    return std::make_pair(LaserInteraction::DEFLECT, this->GetDeflectedLaserDirection(incomingLaser));
  }

  else {
    return std::make_pair(LaserInteraction::HIT, ZERO_VECTOR);
  }
}

Vector Deflector::GetDeflectedLaserDirection(Vector laserDirection) const {
  switch (this->orient) {
    case Orientation::SOUTH_WEST: {
      if (laserDirection == UP_VECTOR) {
        return LEFT_VECTOR;
      }

      else if (laserDirection == RIGHT_VECTOR) {
        return DOWN_VECTOR;
      }
      break;
    }

    case Orientation::NORTH_EAST: {
      if (laserDirection == DOWN_VECTOR) {
        return RIGHT_VECTOR;
      }

      else if (laserDirection == LEFT_VECTOR) {
        return UP_VECTOR;
      }
      break;
    }

    case Orientation::SOUTH_EAST: {
      if (laserDirection == UP_VECTOR) {
        return RIGHT_VECTOR;
      }

      else if (laserDirection == LEFT_VECTOR) {
        return DOWN_VECTOR;
      }
      break;
    }

    case Orientation::NORTH_WEST: {
      if (laserDirection == DOWN_VECTOR) {
        return LEFT_VECTOR;
      }

      else if (laserDirection == RIGHT_VECTOR) {
        return UP_VECTOR;
      }
      break;
    }

    default: {
      return ZERO_VECTOR;
      break;
    }
  }
}

// void Deflector::RotateLeft()
// {
//     switch (this->GetOrientation()) {
//         case SOUTH:
//         {
//             this->Orientation = WEST;
//             break;
//         }

//         case WEST:
//         {
//             this->Orientation = NORTH;
//             break;
//         }

//         case NORTH:
//         {
//             this->Orientation = EAST;
//             break;
//         }

//         case EAST:
//         {
//             this->Orientation = SOUTH;
//             break;
//         }
//     }
// }

// void Deflector::RotateRight()
// {
//     switch (this->GetOrientation()) {
//         case SOUTH:
//         {
//             this->Orientation = EAST;
//             break;
//         }

//         case WEST:
//         {
//             this->Orientation = SOUTH;
//             break;
//         }

//         case NORTH:
//         {
//             this->Orientation = WEST;
//             break;
//         }

//         case EAST:
//         {
//             this->Orientation = NORTH;
//             break;
//         }
//     }
// }

int Deflector::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const {
  return 225 / (piecePosition - opKingPosition).CalculateManHatDistance();
}
}  // namespace laser::game
