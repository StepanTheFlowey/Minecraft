#pragma once

#include "main.hpp"

enum class Side: uint8_t {
  Null = 0,         //0b00000000

  None = 1 << 0,    //0b00000001
  All = 1 << 1,     //0b00000010
  Full = 63 << 2,   //0b11111100

  Up = 1 << 2,      //0b00000100
  Down = 1 << 3,    //0b00001000

  Forward = 1 << 4, //0b00010000
  North = 1 << 4,   //0b00010000

  Back = 1 << 5,    //0b00100000
  South = 1 << 5,   //0b00100000

  Left = 1 << 6,    //0b01000000
  West = 1 << 6,    //0b01000000

  Right = 1 << 7,   //0b10000000
  East = 1 << 7     //0b10000000
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

inline Side operator ^ (const Side l, const Side r) {
  using T = std::underlying_type_t<Side>;
  return static_cast<Side>(static_cast<T>(l) ^ static_cast<T>(r));
}

inline Side& operator ^= (Side& l, const Side r) {
  l = l ^ r;
  return l;
}
