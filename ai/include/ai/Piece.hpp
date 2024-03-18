#ifndef PIECE_HPP
#define PIECE_HPP
#include <utility>
#include "ai/Vector.hpp"

typedef enum pieceColors_tag {
    BLUE = 0,
    RED,
    NONE,
} PieceColors_t;

typedef enum pieceType_tag {
    SWITCH = 0,
    DEFLECTOR,
    DEFENDER,
    KING,
    LASER
} PieceType_t;

typedef enum Orientation_tag {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,
    NO_ORIENTATION,
} Orientation_t;

typedef enum LaserDirections_tag {
    UP = 0,
    DOWN,
} LaserDirection_t;

typedef enum LaserInteraction_tag {
    BLOCK,
    DEFLECT,
    HIT
} LaserInteraction_t;

class Piece {
protected:
    int NumberOfOrientations;
    Orientation_t Orientation;
    PieceColors_t PieceColor;
    PieceType_t PieceType;
    char PieceChar;
    bool SwitchAllowed;
public: 
    Piece(PieceColors_t color, Orientation_t orientation) : NumberOfOrientations(0), PieceType(), PieceColor(color), Orientation(orientation) {}

    PieceColors_t GetPieceColor() {
        return this->PieceColor;
    }

    Orientation_t GetOrientation() {
        return this->Orientation;
    }

    int GetNumOrientations() {
        return this->NumberOfOrientations;
    }

    PieceType_t GetPieceType() {
        return this->PieceType;
    }

    bool GetSwitchPermission() {
        return this->SwitchAllowed;
    }
    virtual ~Piece() = default;

    virtual std::pair<LaserInteraction_t, Vector> GetLaserInteraction(Vector incomingLaser) const = 0;
    virtual Orientation_t LaserDirectionToOrientation(Vector laserDirection) const = 0;
    virtual Vector GetDeflectedLaserDirection(Vector laserDirection) const = 0;
    virtual int GetPieceScore(Vector piecePosition, Vector ownKingPosition, Vector opKingPosition) const = 0;
};

#endif