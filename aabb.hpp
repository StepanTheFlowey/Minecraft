#pragma once
#include "vec.hpp"

template <typename T> class Aabb {
public:
  T minX = 0;
  T minY = 0;
  T minZ = 0;
  T maxX = 0;
  T maxY = 0;
  T maxZ = 0;

  Aabb() {

  }

  Aabb(Vec3<T> v0, Vec3<T> v1) {
    minX = v0.x;
    minY = v0.y;
    minZ = v0.z;
    maxX = v1.x;
    maxY = v1.y;
    maxZ = v1.z;
  }

  Aabb(T x0, T y0, T z0, T x1, T y1, T z1) {
    minX = x0;
    minY = y0;
    minZ = z0;
    maxX = x1;
    maxY = y1;
    maxZ = z1;
  }

  bool intersects(Aabb<T> aabb) {
    intersects(aabb.minX, aabb.minY, aabb.minZ, aabb.maxX, aabb.maxY, aabb.maxZ);
  }

  bool intersects(T x0, T y0, T z0, T x1, T y1, T z1) {
    return minX < x1 &&maxX > x0 && minY < y1 &&maxY > y0 && minZ < z1 &&maxZ > z0;
  }
};