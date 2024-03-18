#ifndef LASER_HPP
#define LASER_HPP

#include "Piece.hpp"

class Laser : public Piece {
public:
    Laser(PieceColors_t pieceColor, Orientation_t orientation) : Piece(pieceColor, orientation) {
        this->NumberOfOrientations = 1;
        this->PieceType = LASER;
        this->PieceChar = (pieceColor == BLUE) ? 'L' : 'l';
    };

    std::pair<LaserInteraction_t, Vector> GetLaserInteraction(Vector incomingLaser) const override;
    Orientation_t LaserDirectionToOrientation(Vector laserDirection) const override;
    Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
    int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;
};

#endif