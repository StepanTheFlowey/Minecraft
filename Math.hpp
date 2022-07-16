#pragma once

#include "main.hpp"
#include "Triangle3.hpp"
#include "Rect3.hpp"
#include "Plane3.hpp"
#include "CollisionResult.hpp"

constexpr double_t PI = 3.1415926535897932384626433832795;
constexpr double_t DEG_TO_RAD = 0.017453292519943295769236907684886;
constexpr double_t EPS = 1e-6;

constexpr float_t F_PI = 3.1415926535897932384626433832795F;
constexpr float_t F_DEG_TO_RAD = 0.017453292519943295769236907684886F;
constexpr float_t F_EPS = 1e-6F;

using SmallPos = Vec3<uint8_t>;

namespace math {
  template <typename T>
  CollisionResult<T> planeLineCollision(
    const Plane3<T>& plane,
    const Vec3<T>& lineBegin,
    const Vec3<T>& lineEnd
  );

  template <typename T>
  CollisionResult<T> triangleLineCollision(
    const Triangle3<T>& triangle,
    const Vec3<T>& normal,
    const Vec3<T>& lineBegin,
    const Vec3<T>& lineEnd
  );

  template <typename T>
  CollisionResult<T> rectLineCollision(
    const Rect3<T>& rect,
    const Vec3<T>& normal,
    const Vec3<T>& lineBegin,
    const Vec3<T>& lineEnd
  );
}

#include "Math.inl"
