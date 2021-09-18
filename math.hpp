#pragma once
#include "aabb.hpp"
#include "vec.hpp"
#include "plane.hpp"
#include <cmath>

template <typename T> Vec3<T> vectorProduct(Vec3<T> A, Vec3<T> B) {
  return Vec3<T>(A.y * B.z - A.z * B.y,
                 A.z * B.x - A.x * B.z,
                 A.x * B.y - A.y * B.z);
}

template <typename T> T dotProduct(Vec3<T> A, Vec3<T> B) {
  return A.x * B.x + A.y * B.y + A.z * B.z;
}

template <typename T> Vec3<T> getNormal(Vec3<T> A, Vec3<T> B, Vec3<T> C) {
  return vectorProduct(B - A, C - A);
}

template <typename T> Vec3<T> getNormal(Plane<T> p) {
  Vec3<T> A(p.x, p.y, p.z);
  Vec3<T> B = A;
  Vec3<T> C = A;
  if(p.vX == 0) {
    B.y += p.vY;
    C.z += p.vZ;
  }
  if(p.vY == 0) {
    B.x += p.vX;
    C.z += p.vZ;
  }
  if(p.vZ == 0) {
    B.x += p.vX;
    C.y += p.vY;
  }
  return getNormal(A, B, C);
}