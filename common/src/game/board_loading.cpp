#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "common/game/board.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/game/pieces/defender.hpp"
#include "common/game/pieces/deflector.hpp"
#include "common/game/pieces/king.hpp"
#include "common/game/pieces/laser.hpp"
#include "common/game/pieces/piece.hpp"
#include "common/game/pieces/switch.hpp"
#include "common/game/square.hpp"

namespace laser::game {

bool Board::loadFromString(std::string layoutString) {
  const char *p = layoutString.c_str();

  // Load general board settings
  long nrow = std::strtol(p, (char **)&p, 10);
  long ncol = std::strtol(p, (char **)&p, 10);
  board = std::vector<std::vector<Square>>(nrow);
  for (auto &col : board) col.resize(ncol);

  // Set tiles informations
  for (int row = 0; row < nrow; row++) {
    for (int col = 0; col < ncol; col++) {
      board[row][col].Position = Vector{row, col};

      if ((col == 0) || (col == ncol - 2 && (row == 0 || row == nrow - 1)))
        board[row][col].ReservedSquare = PieceColor::RED;
      if ((col == ncol - 1) || (col == 1 && (row == 0 || row == nrow - 1)))
        board[row][col].ReservedSquare = PieceColor::BLUE;
    }
  }

  // Load pieces
  long npieces = std::strtol(p, (char **)&p, 10);
  for (long i = 0; i < npieces; i++) {
    long x = std::strtol(p, (char **)&p, 10);
    long y = std::strtol(p, (char **)&p, 10);
    long c = std::strtol(p, (char **)&p, 10);
    char t = *(++p)++;
    long o = std::strtol(p, (char **)&p, 10);

    // Translate color
    auto color = (c == 0) ? PieceColor::BLUE : PieceColor::RED;

    // Translate orientation
    Orientation orient;
    switch (o) {
      case 0:
        orient = Orientation::NORTH;
        break;
      case 1:
        orient = Orientation::EAST;
        break;
      case 2:
        orient = Orientation::SOUTH;
        break;
      default:
        orient = Orientation::WEST;
    }

    // Make Piece
    std::shared_ptr<game::Piece> piece;
    if (t == 'L')
      piece = std::make_shared<game::Laser>(color, orient);
    else if (t == 'K')
      piece = std::make_shared<game::King>(color, orient);
    else if (t == 'D')
      piece = std::make_shared<game::Defender>(color, orient);
    else if (t == 'S')
      piece = std::make_shared<game::Switch>(color, orient);
    else
      piece = std::make_shared<game::Deflector>(color, orient);
    board[x][y].Piece = piece;

    std::cout << "Found piece " << t << " at " << x << ", " << y << " of color " << c << " and orientation " << o
              << std::endl;
  }

  populatePiecesSets();

  return true;
}

}  // namespace laser::game