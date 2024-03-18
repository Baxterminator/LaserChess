#include <memory>
#include "ai/Board.hpp"
#include "ai/Move.hpp"
#include "ai/Piece.hpp"
#include "ai/Square.hpp"

bool ValidateMove(Vector startPosition, Vector endPosition)
{
    bool returnVal = false;

    if (abs(endPosition.y - startPosition.y) <= 1 && abs(endPosition.x - startPosition.x) <= 1 &&
        !(startPosition == endPosition)) {
        returnVal = true;
    }

    return returnVal;
}

bool ValidatePosition(Vector position)
{
    bool returnVal = false;
    if ((position.x >= 0) && (position.x < COLUMN_COUNT) && (position.y >= 0) && (position.y < ROW_COUNT)) {
        returnVal = true;
    }

    return returnVal;
}

bool ShiftMove::LegalMove(const Board_t& board, PieceColors_t playerColor) const
{
    if (!ValidateMove(this->StartPosition, this->EndPosition) && ValidatePosition(this->StartPosition) && ValidatePosition(this->EndPosition))
    {
        return false;
    }

    Square startSq = board[this->StartPosition.y][this->StartPosition.x];
    Square endSq = board[this->EndPosition.y][this->EndPosition.x];
    PieceColors_t oppositeColor = (playerColor == BLUE) ? RED : BLUE;
    if ((endSq.ReservedSquare == oppositeColor) || endSq.Piece || (startSq.Piece == nullptr)) {
        return false;
    }

    return true;
}

void ShiftMove::ApplyMove(Board& board)
{
    Square& startSq = board.board[this->StartPosition.y][this->StartPosition.x];
    Square& endSq = board.board[this->EndPosition.y][this->EndPosition.x];
    std::shared_ptr<Piece> piece = startSq.Piece;
    PieceColors_t pieceColor = piece->GetPieceColor();
    startSq.Piece = nullptr;
    endSq.Piece = piece;
    if (pieceColor == BLUE) {
        board.BluePiecesSquares.erase(startSq);
        board.BluePiecesSquares.insert(endSq);
    }

    else {
        board.RedPiecesSquares.erase(startSq);
        board.RedPiecesSquares.insert(endSq);
    }
}

bool SwitchMove::LegalMove(const Board_t& board, PieceColors_t playerColor) const
{
    if (!ValidateMove(this->StartPosition, this->EndPosition) && ValidatePosition(this->StartPosition) && ValidatePosition(this->EndPosition))
    {
        return false;
    }

    Square startSq = board[this->StartPosition.y][this->StartPosition.x];
    Square endSq = board[this->StartPosition.y][this->EndPosition.y];
    if ((startSq.Piece == nullptr) || (endSq.Piece == nullptr) || (startSq.Piece->GetPieceType() != SWITCH) ) {
        return false;
    }

    if ((endSq.ReservedSquare != playerColor) || (endSq.Piece->GetSwitchPermission())) {
        return false;
    }

    return true;
}

void SwitchMove::ApplyMove(Board& board)
{
    Square& startSq = board.board[this->StartPosition.y][this->StartPosition.x];
    Square& endSq = board.board[this->EndPosition.y][this->EndPosition.y];
    std::shared_ptr<Piece> startPiece = startSq.Piece;
    std::shared_ptr<Piece> endPiece = endSq.Piece;
    std::unordered_set<Square, Square::HashFunction>& startPieceSquares = (startPiece->GetPieceColor() == BLUE) ? board.BluePiecesSquares : board.RedPiecesSquares;
    std::unordered_set<Square, Square::HashFunction>& endPieceSquares = (endPiece->GetPieceColor() == BLUE) ? board.BluePiecesSquares : board.RedPiecesSquares;
    
    std::shared_ptr<Piece> tmp = endSq.Piece;
    endSq.Piece = startSq.Piece;
    startSq.Piece = tmp;

    startPieceSquares.erase(startSq);
    endPieceSquares.erase(endSq);
    startPieceSquares.insert(endSq);
    endPieceSquares.insert(startSq);
}