#pragma once

#include "types.hpp"
#include "vec3.hpp"
#include "plane.hpp"
#include "rayTraceResult.hpp"

constexpr double_t PI = 3.1415926535897932384626433832795;
constexpr double_t DEG_TO_RAD = 0.017453292519943295769236907684886;
constexpr float_t DEG_TO_RAD_F = 0.01745329238F;

using SmallPos = Vec3<uint8_t>;

namespace math {
  template <typename T> inline Vec3<T> vectorProduct(Vec3<T> A, Vec3<T> B);

  template <typename T> inline T dotProduct(Vec3<T> A, Vec3<T> B);

  template <typename T> inline Vec3<T> getNormal(Vec3<T> A, Vec3<T> B, Vec3<T> C);

  template <typename T> inline Vec3<T> getNormal(Plane<T> plane);

  template <typename T> RayTraceResult<T> planeLineCollision(Plane<T> plane, Vec3<T> normal, Vec3<T> lineBegin, Vec3<T> lineEnd);
}

#include "math.inl"