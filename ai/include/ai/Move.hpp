#ifndef MOVE_HPP
#define MOVE_HPP

#include "ai/Board.hpp"
#include "ai/Piece.hpp"
#include "Vector.hpp"

typedef enum rotationDirections_tag {
    LEFT,
    RIGHT
} RotationDirection_t;

class Move {
public:
    Vector StartPosition;
    Vector EndPosition;
    Move() : StartPosition(ZERO_VECTOR), EndPosition(ZERO_VECTOR) {}
    Move(Vector startPosition, Vector endPosition) : StartPosition(startPosition), EndPosition(endPosition) {}
    virtual ~Move() = default;
    virtual bool LegalMove(const Board_t& board, PieceColors_t playerColor) const = 0;
    virtual void ApplyMove(Board& board) = 0;
    
    // bool operator==(Move& move) {
    //     return this->equals(move);
    // }
};

// Classic shift. Move from one square to the other
class ShiftMove : public Move {
public:

    ShiftMove(Vector startPosition, Vector endPosition) : Move(startPosition, endPosition) {}
    bool LegalMove(const Board_t& board, PieceColors_t playerColor) const override;
    void ApplyMove(Board& board) override;
};

//Switches positions with the piece (Only switches can perform this move)
class SwitchMove : public Move {
public:
    // Vector StartPosition;
    // Vector EndPosition;
    SwitchMove(Vector startPosition, Vector endPosition) : Move(startPosition, endPosition) {}
    bool LegalMove(const Board_t& board, PieceColors_t playerColor) const override;
    void ApplyMove(Board& board) override;
};


class RotateMove : public Move {
public:
    RotationDirection_t RotationDirection;
    Vector PiecePosition;
    RotateMove(Vector piecePosition, RotationDirection_t rotDirection) : RotationDirection(rotDirection), PiecePosition(piecePosition) {}
    RotateMove() {}
    // bool LegalMove(const Board_t& board, PieceColors_t playerColor) override;

};

#endif