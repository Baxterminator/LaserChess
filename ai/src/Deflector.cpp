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
        orientation = NORTH_WEST;
    }

    else if (laserDirection == RIGHT_VECTOR) {
        orientation = NORTH_WEST;
    }

    // else if (laserDirection == LEFT_VECTOR) {
    //     orientation = NORTH_EAST;
    // }

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

        case NORTH_WEST:
        {
            otherAcceptedOrientation = NORTH_EAST;
            break;
        }
    }

    if ((incomingLaser == DOWN_VECTOR) && ((this->Orientation == NORTH_EAST) || (this->Orientation == NORTH_WEST)))
    {
        return std::make_pair(DEFLECT, this->GetDeflectedLaserDirection(incomingLaser));
    }

    else if ((incomingLaser == UP_VECTOR) && (this->Orientation == SOUTH_EAST) && (this->Orientation == SOUTH_WEST)) {
        return std::make_pair(DEFLECT, this->GetDeflectedLaserDirection(incomingLaser));
    }

    else if ((incomingLaser == RIGHT_VECTOR) && (this->Orientation == NORTH_WEST) || (this->Orientation == SOUTH_WEST)) {
        return std::make_pair(DEFLECT, this->GetDeflectedLaserDirection(incomingLaser));
    }

    else if ((incomingLaser == LEFT_VECTOR) && (this->Orientation == NORTH_EAST) || (this->Orientation == SOUTH_EAST)) {
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