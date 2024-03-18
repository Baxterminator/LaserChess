#include <utility>
#include "ai/Laser.hpp"
#include "ai/Piece.hpp"
#include "ai/Vector.hpp"


std::pair<LaserInteraction_t, Vector> Laser::GetLaserInteraction(Vector incomingLaser) const
{
    return std::make_pair(BLOCK, ZERO_VECTOR);
}

Orientation_t Laser::LaserDirectionToOrientation(Vector laserDirection) const
{
    return NO_ORIENTATION;
}

Vector Laser::GetDeflectedLaserDirection(Vector laserDirection) const
{
    return ZERO_VECTOR;
}

int Laser::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const
{
    return 0;
}