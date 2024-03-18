#include <stdlib.h>
#include "ai/Vector.hpp"

bool Vector::operator==(const Vector& v) const {
    return (x == v.x) && (y == v.y);
}

Vector Vector::operator+(const Vector& v) const {
    return {x + v.x, y + v.y};
}

Vector Vector::operator-(const Vector& v) const {
    return {x - v.x, y - v.y};
}

int Vector::CalculateManHatDistance() {
    return abs(x) + abs(y);
}


const Vector UP_VECTOR = { 0, -1 };
const Vector RIGHT_VECTOR = { 1, 0 };
const Vector DOWN_VECTOR = { 0, 1 };
const Vector LEFT_VECTOR = { -1, 0 };
const Vector ZERO_VECTOR = {0, 0};