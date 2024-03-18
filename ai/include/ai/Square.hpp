#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <memory>
#include "Vector.hpp"
#include "Piece.hpp"

class Square {
public: 
    Vector Position;
    std::shared_ptr<Piece> Piece;
    PieceColors_t ReservedSquare; //Some squares are reserved for red/blue

    Square(Vector position, PieceColors_t reservedSquare) : Piece(nullptr), Position(position), ReservedSquare(reservedSquare) {};
    Square() : Piece(nullptr), Position({ -1, -1 }), ReservedSquare(NONE) {};

    bool operator==(const Square& otherSquare) const {
		return this->Position == otherSquare.Position;
	}

    struct HashFunction {
        size_t operator()(const Square& square) const {
            size_t rowHash = std::hash<int>{}(square.Position.y);
            size_t colHash = std::hash<int>{}(square.Position.x);
            return rowHash * 37 + colHash;
        }
    };
};



#endif