#include "common/game/board.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

#include "common/game/move.hpp"
#include "common/game/move_evaluation.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/game/pieces/defender.hpp"
#include "common/game/pieces/deflector.hpp"
#include "common/game/pieces/king.hpp"
#include "common/game/pieces/laser.hpp"
#include "common/game/pieces/piece.hpp"
#include "common/game/pieces/switch.hpp"

// In theory 8 possible moves
static const std::array<Vector, 8> possibleMoveVectors = {Vector{-1, -1}, Vector{0, -1}, Vector{1, -1}, Vector{-1, 0},
                                                          Vector{1, 0},   Vector{-1, 1}, Vector{0, 1},  Vector{1, 1}};

namespace laser::game {

Square* LaserHit(Board& board, PieceColor playerColor) {
  Vector position = playerColor == PieceColor::BLUE ? Vector{COLUMN_COUNT - 1, ROW_COUNT - 1} : Vector{0, 0};
  Vector laserDirection = playerColor == PieceColor::BLUE ? Vector{0, -1} : Vector{0, 1};
  // calculating laser trajectory
  position = position + laserDirection;
  while (position.x >= 0 && position.x < COLUMN_COUNT && position.y >= 0 && position.y < ROW_COUNT) {
    Square& currentSquare = board.board[position.y][position.x];
    std::shared_ptr<Piece> currentPiece = currentSquare.Piece;
    if (currentPiece != nullptr) {
      std::pair<LaserInteraction, Vector> laserInteraction = currentPiece->GetLaserInteraction(laserDirection);
      switch (laserInteraction.first) {
        case LaserInteraction::DEFLECT: {
          laserDirection = laserInteraction.second;
          break;
        }

        case LaserInteraction::HIT: {
          return &currentSquare;
          break;
        }

        case LaserInteraction::BLOCK: {
          return nullptr;
          break;
        }
      }
    }
    position = position + laserDirection;
  }
  return nullptr;
}

std::shared_ptr<Piece> Board::RemoveLaserHitPiece(Square* pHitSquare) {
  std::shared_ptr<Piece> hitPiece = pHitSquare->Piece;
  try {
    std::shared_ptr<Piece> hitPiece = pHitSquare->Piece;
    if (pHitSquare->Piece->GetPieceColor() == PieceColor::BLUE) {
      this->BluePiecesSquares.erase(*pHitSquare);
      // Piece is destroyed
      pHitSquare->Piece = nullptr;
    }

    else if (pHitSquare->Piece->GetPieceColor() == PieceColor::RED) {
      this->RedPiecesSquares.erase(*pHitSquare);
      // Piece is destroyed
      pHitSquare->Piece = nullptr;
    }
    return hitPiece;
  } catch (...) {
    std::cout << "something went wrong" << std::endl;
  }

  return hitPiece;
}

Vector FindKingPosition(std::unordered_set<Square, Square::HashFunction>& pieceSquares) {
  for (const Square& pieceSq : pieceSquares) {
    if (pieceSq.Piece->GetPieceType() == PieceType::KING) {
      return pieceSq.Position;
    }
  }

  return {-1, -1};
}

Orientation bestLaserOrientation(PieceType pieceType, int laserPos) {
  Orientation orientation = Orientation::NO_ORIENTATION;
  if (pieceType == PieceType::DEFLECTOR) {
    // red laser
    if (laserPos == 0) {
      orientation = Orientation::NORTH_EAST;
    }
    // blue laser
    else if (laserPos == (COLUMN_COUNT - 1)) {
      orientation = Orientation::SOUTH_WEST;
    }
  }

  else if (pieceType == PieceType::SWITCH) {
    // red laser
    if (laserPos == 0) {
      orientation = Orientation::NORTH_EAST;
    }

    else if (laserPos == (COLUMN_COUNT - 1)) {
      orientation = Orientation::NORTH_WEST;
    }
  }

  return orientation;
}

float EvaluatePiece(std::unordered_set<Square, Square::HashFunction>& pieceSquares, Vector ownKingPosition,
                    Vector opKingPosition, int laserPos) {
  float score = 0;
  for (const Square& pieceSq : pieceSquares) {
    std::shared_ptr piece = pieceSq.Piece;
    PieceType pieceType = piece->GetPieceType();
    //
    if (pieceType == PieceType::DEFLECTOR || pieceType == PieceType::SWITCH) {
      // piece is on either axis of the king
      if (pieceSq.Position.x == opKingPosition.x || pieceSq.Position.y == opKingPosition.y) {
        score += 200;
      }

      // Piece is intercepting the laser
      if (pieceSq.Position.x == laserPos) {
        score += 100;
        if (piece->GetOrientation() == bestLaserOrientation(pieceType, laserPos)) {
          score += 300;
        }
      }
    }
  }

  return score;
}

float EvaluatePosition(Board& board, PieceColor playerColor) {
  float totalScore = 0.0f;

  Vector BlueKingPosition = FindKingPosition(board.BluePiecesSquares);
  Vector RedKingPosition = FindKingPosition(board.RedPiecesSquares);

  // Blue has no king, red has won
  if (BlueKingPosition == Vector{-1, -1}) {
    return std::numeric_limits<float>::max();
  } else if (RedKingPosition == Vector{-1, -1}) {
    return std::numeric_limits<float>::min();
  }

  totalScore += EvaluatePiece(board.BluePiecesSquares, BlueKingPosition, RedKingPosition, COLUMN_COUNT - 1);
  totalScore += EvaluatePiece(board.RedPiecesSquares, RedKingPosition, BlueKingPosition, 0);

  return totalScore;
}

// Applies to the move to the boardstatus and calculates if anything is hit by the laser
void MakeMove(Board& board, std::shared_ptr<Move> move, PieceColor playerColor) {
  move->ApplyMove(board);
  Square* laserHitSquare = LaserHit(board, playerColor);
  std::shared_ptr<Piece> laserHitPiece = nullptr;
  if (laserHitSquare) {
    laserHitPiece = board.RemoveLaserHitPiece(laserHitSquare);
  }
}

std::vector<std::shared_ptr<Move>> FindLegalMoves(const Board_t& board, const Square& sq) {
  if (!sq.Piece) {
    // Somenthing went wrong
    return {};
  }

  std::vector<std::shared_ptr<Move>> moves;
  for (Vector MoveVector : possibleMoveVectors) {
    std::shared_ptr<ShiftMove> shiftMove = std::make_shared<ShiftMove>(sq.Position, sq.Position + MoveVector);
    if ((shiftMove->StartPosition.x >= 0) && (shiftMove->StartPosition.x < COLUMN_COUNT) &&
        (shiftMove->StartPosition.y >= 0) && (shiftMove->StartPosition.y < ROW_COUNT) &&
        (shiftMove->EndPosition.x >= 0) && (shiftMove->EndPosition.x < COLUMN_COUNT) &&
        (shiftMove->EndPosition.y >= 0) && (shiftMove->EndPosition.y < ROW_COUNT)) {
      if (shiftMove->LegalMove(board, sq.Piece->GetPieceColor())) {
        moves.push_back(shiftMove);
      }
    }
    std::shared_ptr<SwitchMove> switchMove = std::make_shared<SwitchMove>(sq.Position, sq.Position + MoveVector);
    if ((switchMove->StartPosition.x >= 0) && (switchMove->StartPosition.x < COLUMN_COUNT) &&
        (switchMove->StartPosition.y >= 0) && (switchMove->StartPosition.y < ROW_COUNT) &&
        (switchMove->EndPosition.x >= 0) && (switchMove->EndPosition.x < COLUMN_COUNT) &&
        (switchMove->EndPosition.y >= 0) && (switchMove->EndPosition.y < ROW_COUNT)) {
      if (switchMove->LegalMove(board, sq.Piece->GetPieceColor())) {
        moves.push_back(switchMove);
      }
    }
  }

  return moves;
}

void ApplyMove(Board& board, Move& move) {}

void Board::populatePiecesSets() {
  std::shared_ptr<Piece> curPiece = nullptr;
  for (int i = 0; i < ROW_COUNT; i++) {
    for (int j = 0; j < COLUMN_COUNT; j++) {
      Square square = this->board[i][j];

      if (square.Piece != nullptr) {
        if (square.Piece->GetPieceColor() == PieceColor::BLUE) {
          this->BluePiecesSquares.insert(square);
        }

        else if (square.Piece->GetPieceColor() == PieceColor::RED) {
          this->RedPiecesSquares.insert(square);
        }
      }
    }
  }
}

std::string MoveToStringRepresentation(std::shared_ptr<Move> move) {
  std::string startColumn = std::to_string(move->StartPosition.x);
  std::string startRow = std::to_string(move->StartPosition.y);
  std::string endColumn = std::to_string(move->EndPosition.x);
  std::string endRow = std::to_string(move->EndPosition.y);

  std::string moveStringRepresentation =
      ";move " + startRow + " " + startColumn + " " + endRow + " " + endColumn + "\n";
  return moveStringRepresentation;
}

void StringToMove(std::string moveString, Board& board) {
  std::stringstream strStream;
  strStream << moveString.substr(6);
  std::vector<int> numbers;
  for (int i = 0; strStream >> i;) {
    numbers.push_back(i);
    // std::cout << i << " ";
  }

  int startRow = numbers[0];
  int startColumn = numbers[1];
  int endRow = numbers[2];
  int endColumn = numbers[3];

  Vector startPosition = {startRow, startColumn};
  Vector endPosition = {endRow, endColumn};
  // Switch places?
  if (board.board[endRow][endColumn].Piece == nullptr) {
    std::shared_ptr<ShiftMove> shiftMove = std::make_shared<ShiftMove>(ShiftMove(startPosition, endPosition));
    MakeMove(board, shiftMove, PieceColor::RED);
  }

  else {
    std::shared_ptr<SwitchMove> switchMove = std::make_shared<SwitchMove>(SwitchMove(startPosition, endPosition));
    MakeMove(board, switchMove, PieceColor::RED);
  }
}

std::string FindBestMove(PieceColor playerColor, Board& board) {
  float bestEval = 0.0f;
  std::unordered_set<Square, Square::HashFunction> playerSquares;
  if (playerColor == PieceColor::BLUE) {
    playerSquares = board.BluePiecesSquares;
  } else {
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
  // Sorts the moves by highest "score"
  std::sort(std::begin(evaluationResults), std::end(evaluationResults),
            [](MoveEvaluation a, MoveEvaluation b) { return a.Evaluation > b.Evaluation; });
  // Applies the move to the board.
  MakeMove(board, evaluationResults[0].Move, playerColor);
  std::string moveStringRepresentation = MoveToStringRepresentation(evaluationResults[0].Move);
  return moveStringRepresentation;
}

PieceColor Board::hasSomeoneWon() {
  auto blue = FindKingPosition(BluePiecesSquares);
  auto red = FindKingPosition(RedPiecesSquares);

  return (blue.x == -1 || blue.y == -1) ? PieceColor::RED
                                        : ((red.x == -1 || red.y == -1) ? PieceColor::BLUE : PieceColor::NONE);
}

}  // namespace laser::game