#include <utility>
#include "ai/Switch.hpp"
#include "ai/Piece.hpp"
#include "ai/Vector.hpp"


Orientation_t Switch::LaserDirectionToOrientation(Vector laserDirection) const
{
    Orientation_t orientation = NO_ORIENTATION;
    if (laserDirection == UP_VECTOR) {
        orientation = NORTH_WEST;
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

std::pair<LaserInteraction_t, Vector> Switch::GetLaserInteraction(Vector incomingLaser) const
{
    Orientation_t laserOrientation = this->LaserDirectionToOrientation(incomingLaser);
    Vector newLaserDirection = this->GetDeflectedLaserDirection(incomingLaser);
    return std::make_pair(DEFLECT, newLaserDirection);
}

Vector Switch::GetDeflectedLaserDirection(Vector laserDirection) const
{
    switch(this->Orientation) {
        case NORTH_EAST:
        {
            if (laserDirection == DOWN_VECTOR) {
                return RIGHT_VECTOR;
            }

            else if (laserDirection == LEFT_VECTOR) {
                return DOWN_VECTOR;
            }
            break;
        }

        case NORTH_WEST:
        {
            if (laserDirection == UP_VECTOR) {
                return LEFT_VECTOR;
            }

            else if (laserDirection == LEFT_VECTOR) {
                return UP_VECTOR;
            }
            break;
        }

        case SOUTH_WEST:
        case SOUTH_EAST:
        default:
        {
            return ZERO_VECTOR;
            break;
        }
    }
}



int Switch::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const
{
    return 1500 / (piecePosition - opKingPosition).CalculateManHatDistance();
}