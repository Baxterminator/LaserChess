#ifndef DEFLECTOR_HPP
#define DEFLECTOR_HPP
#include "Piece.hpp"

class Deflector : public Piece {
public: 
    Deflector(PieceColors_t pieceColor, Orientation_t orientation) : Piece(pieceColor, orientation) {
        this->NumberOfOrientations = 4;
        this->PieceType = DEFLECTOR;
        this->PieceChar = (pieceColor == BLUE) ? 'D' : 'd';
        this->SwitchAllowed = true;
    }

    std::pair<LaserInteraction_t, Vector> GetLaserInteraction(Vector incomingLaser) const override;
    Orientation_t LaserDirectionToOrientation(Vector laserDirection) const override;
    Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
    int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;

    // void RotateLeft();
    // void RotateRight();
};

#endif