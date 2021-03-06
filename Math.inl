#pragma once

#include <cmath>

template <typename T>
CollisionResult<T> math::planeLineCollision(
  const Plane3<T>& plane,
  const Vec3<T>& lineBegin,
  const Vec3<T>& lineEnd
) {
  CollisionResult<T> result;

  Vec3<T> lineDirection = lineEnd - lineBegin;

  T CM = plane.normal.dotProduct(lineDirection);
  if(abs(CM) < EPS) {
    return result;
  }

  T CN = plane.normal.dotProduct(plane.point - lineBegin);
  if(CN > 0.0) {
    return result;
  }

  T K = CN / CM;
  if(K < 0.0 || K > 1.0) {
    return result;
  }

  result.pos = lineDirection * K + lineBegin;
  result.hit = true;

  return result;
}

template <typename T>
CollisionResult<T> math::triangleLineCollision(
  const Triangle3<T>& triangle,
  const Vec3<T>& normal,
  const Vec3<T>& lineBegin,
  const Vec3<T>& lineEnd
) {
  CollisionResult<T> result;

  result = planeLineCollision(Plane3<T>(triangle.a, normal), lineBegin, lineEnd);
  if(result.hit) {
    result.hit = triangle.isPointInside(result.hit);
  }

  return result;
}

template <typename T>
CollisionResult<T> math::rectLineCollision(
  const Rect3<T>& rect,
  const Vec3<T>& normal,
  const Vec3<T>& lineBegin,
  const Vec3<T>& lineEnd
) {
  CollisionResult<T> result;

  result = planeLineCollision(Plane3<T>(rect.a, normal), lineBegin, lineEnd);
  if(result.hit) {
    result.hit = rect.isPointInside(result.pos);
  }

  return result;
}
