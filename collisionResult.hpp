#pragma once

#include "vec3.hpp"
#include "side.hpp"

template <typename T> struct CollisionResult {
  bool hit = false;
  Vec3<T> pos;
};

using CollisionResultd = CollisionResult<GLdouble>;
using CollisionResultf = CollisionResult<GLfloat>;