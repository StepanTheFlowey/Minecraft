#pragma once

#include <cmath>

template <typename T> inline Vec3<T> math::vectorProduct(Vec3<T> A, Vec3<T> B) {
  return Vec3<T>(A.y * B.z - A.z * B.y,
                 A.z * B.x - A.x * B.z,
                 A.x * B.y - A.y * B.x);
}

template <typename T> inline T math::dotProduct(Vec3<T> A, Vec3<T> B) {
  return A.x * B.x + A.y * B.y + A.z * B.z;
}

template <typename T> T math::triangleSquare(T a, T b, T c) {
  T p = (a + b + c) / 2;
  return sqrt(p * (p - a) * (p - b) * (p - c));
}

template <typename T> bool math::isPointOnTriangle(Triangle<T> triangle, Vec3<T> point) {
  bool inside = 0;
  T AB = sqrt((triangle.A.x - triangle.B.x) * (triangle.A.x - triangle.B.x) + (triangle.A.y - triangle.B.y) * (triangle.A.y - triangle.B.y) + (triangle.A.z - triangle.B.z) * (triangle.A.z - triangle.B.z));
  T BC = sqrt((triangle.B.x - triangle.C.x) * (triangle.B.x - triangle.C.x) + (triangle.B.y - triangle.C.y) * (triangle.B.y - triangle.C.y) + (triangle.B.z - triangle.C.z) * (triangle.B.z - triangle.C.z));
  T CA = sqrt((triangle.A.x - triangle.C.x) * (triangle.A.x - triangle.C.x) + (triangle.A.y - triangle.C.y) * (triangle.A.y - triangle.C.y) + (triangle.A.z - triangle.C.z) * (triangle.A.z - triangle.C.z));

  T AP = sqrt((point.x - triangle.A.x) * (point.x - triangle.A.x) + (point.y - triangle.A.y) * (point.y - triangle.A.y) + (point.z - triangle.A.z) * (point.z - triangle.A.z));
  T BP = sqrt((point.x - triangle.B.x) * (point.x - triangle.B.x) + (point.y - triangle.B.y) * (point.y - triangle.B.y) + (point.z - triangle.B.z) * (point.z - triangle.B.z));
  T CP = sqrt((point.x - triangle.C.x) * (point.x - triangle.C.x) + (point.y - triangle.C.y) * (point.y - triangle.C.y) + (point.z - triangle.C.z) * (point.z - triangle.C.z));
  T diff = (triangleSquare(AP, BP, AB) + triangleSquare(AP, CP, CA) + triangleSquare(BP, CP, BC)) - triangleSquare(AB, BC, CA);
  if(abs(diff) < 1e-10) inside = 1;
  return inside;
}

template <typename T> CollisionResult<T> math::rectLineCollision(Rect<T> rect, Vec3<T> normal, Vec3<T> lineBegin, Vec3<T> lineEnd) {
  CollisionResult<T> result;
  CollisionResult<T> A, B;

  A = triangleLineCollision(Triangle(rect.A, rect.B, rect.C));
  B = triangleLineCollision(Triangle(rect.A, rect.D, rect.C));

  result.hit = A.hit || B.hit;
  if(A.hit) {
    result.pos = A.pos;
  }
  if(B.hit) {
    result.pos = B.pos;
  }
}

template <typename T> CollisionResult<T> math::triangleLineCollision(Triangle<T> triangle, Vec3<T> normal, Vec3<T> lineBegin, Vec3<T> lineEnd) {
  CollisionResult<T> result;

  Vec3<T> lineDirection = lineEnd - lineBegin;

  T CM = math::dotProduct(normal, lineDirection);
  if(abs(CM) < 1e-10) {
    return result;
  }

  T CN = math::dotProduct(normal, triangle.A - lineBegin);
  if(CN < 0.0) {
    return result;
  }

  T K = CN / CM;
  if(K < 0.0 || K > 1.0) {
    return result;
  }

  result.pos = lineDirection * K + lineBegin - triangle.A + Vec3<T>(abs(normal.y) + abs(normal.z), 0.0, 0.0);
  result.hit = isPointOnTriangle(triangle, result.pos);

  return result;
}
