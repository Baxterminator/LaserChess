#ifndef SWITCH_HPP
#define SWITCH_HPP
#include "Piece.hpp"

class Switch : public Piece {
public: 
    Switch(PieceColors_t pieceColor, Orientation_t orientation) : Piece(pieceColor, orientation) {
        this->NumberOfOrientations = 2;
        this->PieceType = SWITCH;
        this->PieceChar = (pieceColor == BLUE) ? 'S' : 's';
        this->SwitchAllowed = false;
    }

    std::pair<LaserInteraction_t, Vector> GetLaserInteraction(Vector incomingLaser) const override;
    Orientation_t LaserDirectionToOrientation(Vector laserDirection) const override;
    Vector GetDeflectedLaserDirection(Vector laserDirection) const override;
    int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const override;
};




#endif