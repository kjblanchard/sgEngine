#pragma once
struct sgPoint {
  int X, Y;
};
inline bool sgPointIsZero(const sgPoint *point) { return point->X && point->Y; }
