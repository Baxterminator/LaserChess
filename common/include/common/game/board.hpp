#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <unordered_set>
#include <vector>

#include "common/game/square.hpp"

namespace laser::game {

#define ROW_COUNT 8
#define COLUMN_COUNT 10

typedef std::vector<std::vector<Square>> Board_t;

class Board {
 public:
  Board_t board;
  std::unordered_set<Square, Square::HashFunction> BluePiecesSquares;
  std::unordered_set<Square, Square::HashFunction> RedPiecesSquares;

  Board(){};
  ~Board(){};

  bool loadFromString(std::string LayoutString);
  void populatePiecesSets();
  std::shared_ptr<Piece> RemoveLaserHitPiece(Square *pHitSquare);

  PieceColor hasSomeoneWon();
};

void FindBestMove(PieceColor playerColor, Board board);

}  // namespace laser::game

#endif