#ifndef LASER_CHESS_PIECES_CONSTANTS
#define LASER_CHESS_PIECES_CONSTANTS

namespace laser::game {

enum class PieceColor {
  BLUE = 0,
  RED,
  NONE,
};

enum class PieceType {
  SWITCH = 0,
  DEFLECTOR,
  DEFENDER,
  KING,
  LASER,
};

enum class Orientation {
  NO_ORIENTATION = -1,
  NORTH = 0,
  NORTH_EAST = NORTH,
  EAST = 1,
  SOUTH_EAST = EAST,
  SOUTH = 2,
  SOUTH_WEST = SOUTH,
  WEST = 3,
  NORTH_WEST = WEST,
};

enum class LaserDirections {
  UP = 0,
  DOWN,
};

enum class LaserInteraction {
  BLOCK,
  DEFLECT,
  HIT,
};

enum class RotationDirection { LEFT, RIGHT };

}  // namespace laser::game

#endif