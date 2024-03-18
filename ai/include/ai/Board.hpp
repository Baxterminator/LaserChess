#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <unordered_set>
#include <array>
#include "Square.hpp"


#define ROW_COUNT 8
#define COLUMN_COUNT 10


typedef std::array<std::array<Square, COLUMN_COUNT>, ROW_COUNT> Board_t;



class Board {
public:
    Board_t board;
    std::unordered_set<Square, Square::HashFunction> BluePiecesSquares;
    std::unordered_set<Square, Square::HashFunction> RedPiecesSquares;

    Board() {};
    ~Board() {};
    bool CreateBoardFromLayoutString(std::string LayoutString);
    void CreateDefaultBoard();
    void PopulatePiecesSets();
    // void FindBestMove(PieceColors_t playerColor);
    std::shared_ptr<Piece> RemoveLaserHitPiece(Square *pHitSquare);
    // void MakeMove(const Move& move);
};

void FindBestMove(PieceColors_t playerColor, Board board);

#endif