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

template <typename T> inline Vec3<T> math::getNormal(Vec3<T> A, Vec3<T> B, Vec3<T> C) {
  return vectorProduct(B - A, C - A);
}

template <typename T> inline Vec3<T> math::getNormal(Plane<T> plane) {
  return getNormal(plane.A, plane.B, plane.C);
}

template <typename T> RayTraceResult<T> math::planeLineCollision(Plane<T> plane,Vec3<T> normal, Vec3<T> lineBegin, Vec3<T> lineEnd) {
  RayTraceResult<T> result;

  Vec3<T> CA = plane.A - lineBegin;     //Vector from A to lineBegin
  Vec3<T> CV = lineEnd - lineBegin;     //Vector from lineEnd to lineBegin

  T CN = math::dotProduct(CA, normal);  //Distance between plane and line
  if(CN <= 0.0) {
    return result;                      //If distance zero return
  }

  T CM = math::dotProduct(CV, normal);
  if(abs(CM) < 1e-6) {
    return result;
  }

  T K = CN / CM;
  if(K < 0.0 || K > 1.0) {
    return result;                       //if k < 0 or k > 1 line does not reach plane
  }

  //Collision point on plane
  result.pos = CV * K + lineBegin - plane.A + Vec3<T>(abs(normal.y) + abs(normal.z), 0.0, 0.0);
  if(
    result.pos.x < 0 ||
    result.pos.y < 0 ||
    result.pos.z < 0 ||
    result.pos.x > 1 ||
    result.pos.y > 1 ||
    result.pos.z > 1
    ) {
    return result;
  }
  result.hit = true;
  return result;
}
