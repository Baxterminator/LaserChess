#include <utility>
#include "ai/Defender.hpp"
#include "ai/Piece.hpp"
#include "ai/Vector.hpp"


Orientation_t Defender::LaserDirectionToOrientation(Vector laserDirection) const
{
    Orientation_t orientation = NO_ORIENTATION;
    if (laserDirection == UP_VECTOR) {
        orientation = SOUTH;
    } 
    
    else if (laserDirection == LEFT_VECTOR) {
        orientation = WEST;
    }

    else if (laserDirection == RIGHT_VECTOR) {
        orientation = EAST;
    }

    else if (laserDirection == DOWN_VECTOR) {
        orientation = NORTH;
    }

    return orientation; 
}

std::pair<LaserInteraction_t, Vector> Defender::GetLaserInteraction(Vector incomingLaser) const
{
    Orientation_t laserOrientation = this->LaserDirectionToOrientation(incomingLaser);
    if (laserOrientation == this->Orientation) {
        return std::make_pair(BLOCK, ZERO_VECTOR);
    }
    
    else {
        return std::make_pair(HIT, ZERO_VECTOR);
    }
}

Vector Defender::GetDeflectedLaserDirection(Vector laserDirection) const
{
    return ZERO_VECTOR;
}

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

int Defender::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const
{
    return  50 / (piecePosition - ownKingPosition).CalculateManHatDistance() - 100 / (piecePosition - opKingPosition).CalculateManHatDistance();
}