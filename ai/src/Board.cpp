#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include "ai/Piece.hpp"
#include "ai/Laser.hpp"
#include "ai/Board.hpp"
#include "ai/Defender.hpp"
#include "ai/Deflector.hpp"
#include "ai/Switch.hpp"
#include "ai/King.hpp"
#include "ai/Move.hpp"
#include "ai/Vector.hpp"
#include "ai/MoveEvaluation.hpp"

// bool Board::CreateBoardFromLayoutString(std::string LayoutString)
// {
//     return false;
// }



//In theory 8 possible moves
static const std::array<Vector, 8> possibleMoveVectors = {
    Vector{-1, -1}, Vector{0, -1}, Vector{1, -1},
    Vector{-1, 0}, Vector{1, 0},
    Vector{-1, 1}, Vector{0, 1}, Vector{1, 1}
};

Square* LaserHit(Board& board, PieceColors_t playerColor)
{
    Vector position = playerColor == BLUE ? Vector{COLUMN_COUNT - 1, ROW_COUNT - 1} : Vector{0, 0};
    Vector laserDirection = playerColor == BLUE ? Vector{0, -1} : Vector{0, 1};
    //calculating laser trajectory
    position = position + laserDirection;
    while (position.x >= 0 && position.x < COLUMN_COUNT && position.y >= 0 && position.y < ROW_COUNT) {
        Square& currentSquare = board.board[position.y][position.x];
        std::shared_ptr<Piece> currentPiece = currentSquare.Piece;
        if (currentPiece != nullptr) {
            std::pair<LaserInteraction_t, Vector> laserInteraction = currentPiece->GetLaserInteraction(laserDirection);
            switch (laserInteraction.first) {
                case DEFLECT:
                {
                    laserDirection = laserInteraction.second;
                    break;
                }


                case HIT:
                {
                    return &currentSquare;
                    break;
                }

                case BLOCK:
                {
                    return nullptr;
                    break;
                }
            }
        }
        position = position + laserDirection;
    }
}


std::shared_ptr<Piece> Board::RemoveLaserHitPiece(Square* pHitSquare)
{
    std::shared_ptr<Piece> hitPiece = pHitSquare->Piece;
    if (pHitSquare->Piece->GetPieceColor() == BLUE) {
        this->BluePiecesSquares.erase(*pHitSquare);
        //Piece is destroyed
        pHitSquare->Piece = nullptr;
    }

    else if (pHitSquare->Piece->GetPieceColor() == RED) {
        this->RedPiecesSquares.erase(*pHitSquare);
        //Piece is destroyed
        pHitSquare->Piece = nullptr;
    }

    return hitPiece;
}

Vector FindKingPosition(std::unordered_set<Square, Square::HashFunction>& pieceSquares)
{
    for (const Square& pieceSq : pieceSquares) {
        if (pieceSq.Piece->GetPieceType() == KING) {
            return pieceSq.Position;
        }
    }

    return {-1, -1};
}

Orientation_t bestLaserOrientation(PieceType_t pieceType, int laserPos)
{
    Orientation_t orientation = NO_ORIENTATION;
    if (pieceType == DEFLECTOR) {
        //red laser
        if (laserPos == 0) {
            orientation = NORTH_EAST;
        }
        //blue laser
        else if (laserPos == (COLUMN_COUNT - 1)) {
            orientation = SOUTH_WEST;
        }
    }

    else if (pieceType == SWITCH) {
        //red laser
        if (laserPos == 0) {
            orientation = NORTH_EAST;
        }

        else if (laserPos == (COLUMN_COUNT - 1)) {
            orientation = NORTH_WEST;
        }
    }

    return orientation;
}

float EvaluatePiece(std::unordered_set<Square, Square::HashFunction>& pieceSquares, Vector ownKingPosition, Vector opKingPosition, int laserPos)
{
    float score = 0;
    for (const Square& pieceSq : pieceSquares) {
        std::shared_ptr piece = pieceSq.Piece;
        PieceType_t pieceType = piece->GetPieceType();
        //
        if (pieceType == DEFLECTOR || pieceType == SWITCH) {
            //piece is on either axis of the king
            if (pieceSq.Position.x == opKingPosition.x || pieceSq.Position.y == opKingPosition.y) {
                score += 200;
            }

            //Piece is intercepting the laser
            if (pieceSq.Position.x == laserPos) { 
                score += 100;
                if (piece->GetOrientation() == bestLaserOrientation(pieceType, laserPos)) {
                    score += 300;
                }
            } 
        }


        //Move defender in front of king if he's exposed
        // else if (pieceType == DEFENDER) {
        //     Vector defendPosition = ownKingPosition - pieceSq.Position;
        // }
    }

    return score;
}

float EvaluatePosition(Board& board, PieceColors_t playerColor)
{
    float totalScore = 0.0f;

    Vector BlueKingPosition = FindKingPosition(board.BluePiecesSquares);
    Vector RedKingPosition = FindKingPosition(board.RedPiecesSquares);

    //Blue has no king, red has won
    if (BlueKingPosition == Vector{-1, -1}) {
        return std::numeric_limits<float>::max();
    }
    else if (RedKingPosition == Vector{-1, -1}) {
        return std::numeric_limits<float>::min();
    }

    totalScore += EvaluatePiece(board.BluePiecesSquares, BlueKingPosition, RedKingPosition, COLUMN_COUNT -1);
    totalScore += EvaluatePiece(board.RedPiecesSquares, RedKingPosition, BlueKingPosition, 0);

    return totalScore;
}

//Applies to the move to the boardstatus and calculates if anything is hit by the laser
void MakeMove(Board& board, std::shared_ptr<Move> move, PieceColors_t playerColor)
{
    move->ApplyMove(board);
    Square* laserHitSquare = LaserHit(board, playerColor);
    std::shared_ptr<Piece> laserHitPiece = nullptr;
    if (laserHitSquare) {
        laserHitPiece = board.RemoveLaserHitPiece(laserHitSquare);
    }
}

std::vector<std::shared_ptr<Move>> FindLegalMoves(const Board_t& board, const Square& sq) {
    if (!sq.Piece) {
        //Somenthing went wrong
        return {};
    }

    std::vector<std::shared_ptr<Move>> moves;
    for (Vector MoveVector : possibleMoveVectors) { 
        std::shared_ptr<ShiftMove> shiftMove = std::make_shared<ShiftMove>(sq.Position, sq.Position + MoveVector);
        if ((shiftMove->StartPosition.x >= 0) && (shiftMove->StartPosition.x < COLUMN_COUNT) && (shiftMove->StartPosition.y >= 0) && (shiftMove->StartPosition.y < ROW_COUNT) &&
            (shiftMove->EndPosition.x >= 0) && (shiftMove->EndPosition.x < COLUMN_COUNT) && (shiftMove->EndPosition.y >= 0) && (shiftMove->EndPosition.y < ROW_COUNT)) 
        {
            if (shiftMove->LegalMove(board, sq.Piece->GetPieceColor())) {
                moves.push_back(shiftMove);
            }
        }
        std::shared_ptr<SwitchMove> switchMove = std::make_shared<SwitchMove>(sq.Position, sq.Position + MoveVector);
        if ((switchMove->StartPosition.x >= 0) && (switchMove->StartPosition.x < COLUMN_COUNT) && (switchMove->StartPosition.y >= 0) && (switchMove->StartPosition.y < ROW_COUNT) &&
            (switchMove->EndPosition.x >= 0) && (switchMove->EndPosition.x < COLUMN_COUNT) && (switchMove->EndPosition.y >= 0) && (switchMove->EndPosition.y < ROW_COUNT))
        { 
            if (switchMove->LegalMove(board, sq.Piece->GetPieceColor())) {
                moves.push_back(switchMove);
            }
        }
    }

    return moves;
}

void ApplyMove(Board& board, Move& move)
{

}

//Populates the board with default setup (for testing purposes)
void Board::CreateDefaultBoard()
{
    Board_t defaultBoard;
    
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COLUMN_COUNT; j++) {
            PieceColors_t resColor = NONE;

            if (j == 0 || (j == COLUMN_COUNT - 2 && (i == 0 || i == COLUMN_COUNT -1))) {
                resColor = RED;
            }

            else if (j == COLUMN_COUNT - 1 || (j == 1 && (i == 0 || i == COLUMN_COUNT - 1))) {
                resColor = BLUE;
            }
            Square sq = Square({j, i}, resColor);
            defaultBoard[i][j] = sq; 
        }
    }

    //populates the pieces according to ACE setup
    //creates the red player pieces
    defaultBoard[0][0].Piece = std::make_shared<Laser>(RED, SOUTH);
    defaultBoard[0][4].Piece = std::make_shared<Defender>(RED, SOUTH);
    defaultBoard[0][5].Piece = std::make_shared<King>(RED, SOUTH);
    defaultBoard[0][6].Piece = std::make_shared<Defender>(RED, SOUTH);
    defaultBoard[0][7].Piece = std::make_shared<Deflector>(RED, SOUTH_EAST);

    defaultBoard[1][2].Piece = std::make_shared<Deflector>(RED, SOUTH_WEST);

    defaultBoard[3][0].Piece = std::make_shared<Deflector>(RED, NORTH_EAST);
    defaultBoard[3][4].Piece = std::make_shared<Switch>(RED, NORTH_WEST);
    defaultBoard[3][5].Piece = std::make_shared<Switch>(RED, NORTH_EAST);
    defaultBoard[3][7].Piece = std::make_shared<Deflector>(RED, SOUTH_EAST);

    defaultBoard[4][0].Piece = std::make_shared<Deflector>(RED, SOUTH_EAST);
    defaultBoard[4][7].Piece = std::make_shared<Deflector>(RED, NORTH_EAST);

    defaultBoard[5][6].Piece = std::make_shared<Deflector>(RED, SOUTH_EAST);

    //Creates the blue player pieces
    defaultBoard[7][2].Piece = std::make_shared<Deflector>(BLUE, NORTH_WEST);
    defaultBoard[7][3].Piece = std::make_shared<Defender>(BLUE, NORTH);
    defaultBoard[7][4].Piece = std::make_shared<King>(BLUE, NORTH);
    defaultBoard[7][5].Piece = std::make_shared<Defender>(BLUE, NORTH);
    defaultBoard[7][9].Piece = std::make_shared<Laser>(BLUE, NORTH);

    defaultBoard[6][7].Piece = std::make_shared<Deflector>(BLUE, NORTH_EAST);

    defaultBoard[4][2].Piece = std::make_shared<Deflector>(BLUE, NORTH_WEST);
    defaultBoard[4][4].Piece = std::make_shared<Switch>(BLUE, NORTH_EAST);
    defaultBoard[4][5].Piece = std::make_shared<Switch>(BLUE, NORTH_WEST);
    defaultBoard[4][9].Piece = std::make_shared<Deflector>(BLUE, SOUTH_WEST);

    defaultBoard[3][2].Piece = std::make_shared<Deflector>(BLUE, SOUTH_WEST);
    defaultBoard[3][9].Piece = std::make_shared<Deflector>(BLUE, NORTH_WEST);

    defaultBoard[2][3].Piece = std::make_shared<Deflector>(BLUE, NORTH_WEST);

    this->board = defaultBoard;

    this->PopulatePiecesSets();

}

void Board::PopulatePiecesSets()
{
    std::shared_ptr<Piece> curPiece = nullptr;
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COLUMN_COUNT; j++) {
            Square square = this->board[i][j];

            if (square.Piece != nullptr) {
                if (square.Piece->GetPieceColor() == BLUE) {
                    this->BluePiecesSquares.insert(square);
                }

                else if (square.Piece->GetPieceColor() == RED) {
                    this->RedPiecesSquares.insert(square);
                }
            }
        }
    }
}


void FindBestMove(PieceColors_t playerColor, Board board)
{
    float bestEval = 0.0f;
    std::unordered_set<Square, Square::HashFunction> playerSquares;
    if (playerColor == BLUE) {
        playerSquares = board.BluePiecesSquares;
    } 
    else {
        playerSquares = board.RedPiecesSquares;
    }

    std::vector<MoveEvaluation> evaluationResults;
    for (const Square& square : playerSquares) {
        for (std::shared_ptr<Move> move : FindLegalMoves(board.board, square)) {
            Board boardCopy = board;
            MakeMove(boardCopy, move, playerColor);
            float evaluationResult = EvaluatePosition(boardCopy, playerColor);
            evaluationResults.push_back({evaluationResult, move});
        }
    }
    //Sorts the moves by highest "score"
    std::sort(std::begin(evaluationResults), std::end(evaluationResults), [](MoveEvaluation a, MoveEvaluation b)
                                                                           { return a.Evaluation > b.Evaluation; } );
    //Applies the move to the board.
    MakeMove(board, evaluationResults[0].Move, playerColor);
}