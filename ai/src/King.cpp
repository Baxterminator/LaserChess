#include <utility>
#include "ai/King.hpp"
#include "ai/Piece.hpp"
#include "ai/Vector.hpp"


std::pair<LaserInteraction_t, Vector> King::GetLaserInteraction(Vector incomingLaser) const
{
    return std::make_pair(HIT, ZERO_VECTOR);
}


Orientation_t King::LaserDirectionToOrientation(Vector laserDirection) const
{
    return NO_ORIENTATION;
}

Vector King::GetDeflectedLaserDirection(Vector laserDirection) const
{
    return ZERO_VECTOR;
}

int King::GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const
{
    return 0;
}