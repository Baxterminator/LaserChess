#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
public:
    King(PieceColors_t pieceColor, Orientation_t orientation) : Piece(pieceColor, orientation) {
        this->NumberOfOrientations = 1;
        this->PieceType = KING;
        this->PieceChar = (pieceColor == BLUE) ? 'K' : 'k';
        this->SwitchAllowed = false;
    };

    std::pair<LaserInteraction_t, Vector> GetLaserInteraction(Vector incomingLaser) const override;
    Orientation_t LaserDirectionToOrientation(Vector laserDirection) const override;
    Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
    int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;

};

#endif