#ifndef LASER_CHESS_VECTOR_HPP
#define LASER_CHESS_VECTOR_HPP

#include <stdlib.h>

typedef unsigned long ulong;

struct Vector {
  // position
  int x, y;

  // Operators
  inline bool operator==(const Vector& v) const { return (x == v.x) && (y == v.y); }
  struct HashFunction {
    ulong operator()(const Vector& v) const;
  };
  Vector operator+(const Vector& v) const { return {x + v.x, y + v.y}; }
  Vector operator-(const Vector& v) const { return {x - v.x, y - v.y}; }

  inline int CalculateManHatDistance() { return abs(x) + abs(y); };
};

inline const Vector DOWN_VECTOR{0, -1};
inline const Vector UP_VECTOR{1, 0};
inline const Vector LEFT_VECTOR{0, 1};
inline const Vector RIGHT_VECTOR{-1, 0};
inline const Vector ZERO_VECTOR{0, 0};

#endif