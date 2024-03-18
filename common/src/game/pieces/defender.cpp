#include "common/game/pieces/defender.hpp"

#include <utility>

#include "common/game/pieces/constants.hpp"

namespace laser::game {

Orientation Defender::LaserDirectionToOrientation(Vector laserDirection) const {
  Orientation orientation = Orientation::NO_ORIENTATION;
  if (laserDirection == UP_VECTOR) {
    orientation = Orientation::SOUTH;
  }

  else if (laserDirection == LEFT_VECTOR) {
    orientation = Orientation::WEST;
  }

  else if (laserDirection == RIGHT_VECTOR) {
    orientation = Orientation::EAST;
  }

  else if (laserDirection == DOWN_VECTOR) {
    orientation = Orientation::NORTH;
  }

  return orientation;
}

std::pair<LaserInteraction, Vector> Defender::GetLaserInteraction(Vector incomingLaser) const {
  Orientation laserOrientation = this->LaserDirectionToOrientation(incomingLaser);
  if (laserOrientation == this->orient) {
    return std::make_pair(LaserInteraction::BLOCK, ZERO_VECTOR);
  }

  else {
    return std::make_pair(LaserInteraction::HIT, ZERO_VECTOR);
  }
}

Vector Defender::GetDeflectedLaserDirection(Vector laserDirection) const { return ZERO_VECTOR; }

// void Defender::RotateLeft()
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

// void Defender::RotateRight()
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

int Defender::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const {
  return 50 / (piecePosition - ownKingPosition).CalculateManHatDistance() -
         100 / (piecePosition - opKingPosition).CalculateManHatDistance();
}

}  // namespace laser::game
