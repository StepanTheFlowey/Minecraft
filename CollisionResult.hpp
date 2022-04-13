#pragma once

#include "Vec3.hpp"
#include "Side.hpp"

template <typename T> struct CollisionResult {
  bool hit = false;
  Vec3<T> pos;
};

using CollisionResultd = CollisionResult<GLdouble>;
using CollisionResultf = CollisionResult<GLfloat>;
