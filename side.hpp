#pragma once
#include "types.hpp"

enum class Side: uint8_t {
  None = 1 << 0,
  All = 1 << 1,
  Up = 1 << 2,
  Down = 1 << 3,

  Forward = 1 << 4,
  North = 1 << 4,

  Back = 1 << 5,
  South = 1 << 5,

  Left = 1 << 6,
  West = 1 << 6,

  Right = 1 << 7,
  East = 1 << 7
};

inline Side operator & (const Side l, const Side r) {
  using T = std::underlying_type_t<Side>;
  return static_cast<Side>(static_cast<T>(l) & static_cast<T>(r));
}

inline Side& operator &= (Side& l, const Side r) {
  l = l & r;
  return l;
}

inline Side operator | (const Side l, const Side r) {
  using T = std::underlying_type_t<Side>;
  return static_cast<Side>(static_cast<T>(l) | static_cast<T>(r));
}

inline Side& operator |= (Side& l, const Side r) {
  l = l | r;
  return l;
}