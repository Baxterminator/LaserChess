#ifndef DEFENDER_HPP
#define DEFENDER_HPP
#include "Piece.hpp"


class Defender : public Piece {
public: 
    Defender(PieceColors_t pieceColor, Orientation_t orientation) : Piece(pieceColor, orientation) {
        this->NumberOfOrientations = 4;
        this->PieceType = DEFENDER;
        this->PieceChar = (pieceColor == BLUE) ? 'B' : 'b';
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