#pragma once
#include "vec.hpp"

enum class Side : uint8_t {
  None = 1 << 0,
  All = 1 << 1,
  Up = 1 << 2,
  Down = 1 << 3,
  North = 1 << 4,
  South = 1 << 5,
  West = 1 << 6,
  East = 1 << 7
};

inline Side operator & (Side &l, Side &r) {
  using T = std::underlying_type_t <Side>;
  return static_cast<Side>(static_cast<T>(l) & static_cast<T>(r));
}

inline Side &operator &= (Side &l, Side &r) {
  l = l & r;
  return l;
}

inline Side operator | (Side &l, Side &r) {
  using T = std::underlying_type_t <Side>;
  return static_cast<Side>(static_cast<T>(l) | static_cast<T>(r));
}

inline Side &operator |= (Side &l, Side &r) {
  l = l | r;
  return l;
}

template <typename T> struct RayTraceResult {
  Vec3<T> pos;
  Side side;
  bool hit = false;
  enum class HitType : bool {
    Block,
    Entity
  };
};

//RayTrace functions defined in math.hpp