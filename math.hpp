#pragma once

#include "types.hpp"
#include "vec3.hpp"
#include "triangle3.hpp"
#include "rect3.hpp"
#include "plane3.hpp"
#include "collisionResult.hpp"

constexpr double_t PI = 3.1415926535897932384626433832795;
constexpr double_t DEG_TO_RAD = 0.017453292519943295769236907684886;
constexpr float_t DEG_TO_RAD_F = 0.01745329238F;
constexpr float_t EPS = 1e-6F;

using SmallPos = Vec3<uint8_t>;

namespace math {
  template <typename T>
  CollisionResult<T> planeLineCollision(Plane3<T> plane, Vec3<T> lineBegin, Vec3<T> lineEnd);

  template <typename T>
  CollisionResult<T> triangleLineCollision(Triangle3<T> triangle, Vec3<T> normal, Vec3<T> lineBegin, Vec3<T> lineEnd);

  template <typename T>
  CollisionResult<T> rectLineCollision(Rect3<T> rect, Vec3<T> normal, Vec3<T> lineBegin, Vec3<T> lineEnd);
}

#include "math.inl"