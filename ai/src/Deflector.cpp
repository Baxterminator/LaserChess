#include <utility>
#include "ai/Deflector.hpp"
#include "ai/Piece.hpp"
#include "ai/Vector.hpp"


Orientation_t Deflector::LaserDirectionToOrientation(Vector laserDirection) const
{
    Orientation_t orientation = NO_ORIENTATION;
    if (laserDirection == UP_VECTOR) {
        orientation = SOUTH_WEST;
    }

    else if (laserDirection == DOWN_VECTOR) {
        orientation = NORTH_EAST;
    }

    else if (laserDirection == RIGHT_VECTOR) {
        orientation = SOUTH_EAST;
    }

    else if (laserDirection == LEFT_VECTOR) {
        orientation = NORTH_WEST;
    }

    return orientation;
}

std::pair<LaserInteraction_t, Vector> Deflector::GetLaserInteraction(Vector incomingLaser) const
{
    Orientation_t laserOrientation = this->LaserDirectionToOrientation(incomingLaser);
    Orientation_t otherAcceptedOrientation = NO_ORIENTATION;
    switch (laserOrientation) {
        case SOUTH_WEST:
        {
            otherAcceptedOrientation = SOUTH_EAST;
            break;
        }

        case NORTH_EAST:
        {
            otherAcceptedOrientation = NORTH_WEST;
            break;
        }

        case SOUTH_EAST:
        {
            otherAcceptedOrientation = SOUTH_WEST;
            break;
        }

        case NORTH_WEST:
        {
            otherAcceptedOrientation = NORTH_EAST;
            break;
        }

        default:
        {
            //should never happen
            break;
        }
    }

    if (laserOrientation == this->Orientation || laserOrientation == otherAcceptedOrientation) {
        return std::make_pair(DEFLECT, this->GetDeflectedLaserDirection(incomingLaser));
    }

    else {
        return std::make_pair(HIT, ZERO_VECTOR);
    }
}



Vector Deflector::GetDeflectedLaserDirection(Vector laserDirection) const
{
    switch(this->Orientation) {
        case SOUTH_WEST:
        {
            if (laserDirection == UP_VECTOR) {
                return LEFT_VECTOR;
            }

            else if (laserDirection == RIGHT_VECTOR) {
                return DOWN_VECTOR;
            }
            break;
        }

        case NORTH_EAST:
        {
            if (laserDirection == DOWN_VECTOR) {
                return RIGHT_VECTOR;
            }

            else if (laserDirection == LEFT_VECTOR) {
                return UP_VECTOR;
            }
            break;
        }

        case SOUTH_EAST:
        {
            if (laserDirection == UP_VECTOR) {
                return RIGHT_VECTOR;
            }

            else if (laserDirection == LEFT_VECTOR) {
                return DOWN_VECTOR;
            }
            break;
        }

        case NORTH_WEST:
        {
            if (laserDirection == DOWN_VECTOR) {
                return LEFT_VECTOR;
            }

            else if (laserDirection == RIGHT_VECTOR) {
                return UP_VECTOR;
            }
            break;
        }

        default:
        {
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

int Deflector::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const
{
    return 225 / (piecePosition - opKingPosition).CalculateManHatDistance();
}