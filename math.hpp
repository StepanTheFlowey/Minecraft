#pragma once
#include <cmath>

#include "block.hpp"
#include "chunk.hpp"
#include "region.hpp"

#define PI 3.1415926535897932384626433832795
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define DEG_TO_RAD_F 0.01745329238F

using SmallPos = Vec3<uint8_t>;

namespace math {
  template <typename T> inline Vec3<T> vectorProduct(Vec3<T> A, Vec3<T> B) {
    return Vec3<T>(A.y * B.z - A.z * B.y,
                   A.z * B.x - A.x * B.z,
                   A.x * B.y - A.y * B.x);
  }

  template <typename T> inline T dotProduct(Vec3<T> A, Vec3<T> B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
  }

  template <typename T> inline Vec3<T> getNormal(Vec3<T> A, Vec3<T> B, Vec3<T> C) {
    return vectorProduct(B - A, C - A);
  }

  template <typename T> inline Vec3<T> getNormal(Plane<T> plane) {
    return getNormal(plane.A, plane.B, plane.C);
  }

  inline ChunkPos getChunkPosFromBlock(BlockPos position) {
    return ChunkPos(position.x >> 4, position.y >> 4, position.z >> 4);
  }

  inline RegionPos getRegionPosFromChunk(ChunkPos position) {
    return RegionPos(position.x >> 4, position.z >> 4);
  }

  inline SmallPos getBlockPosInChunk(BlockPos position) {
    return SmallPos(position.x & 15, position.y & 15, position.z & 15);
  }

  inline SmallPos getChunkPosInRegion(ChunkPos position) {
    return SmallPos(position.x & 15, position.y & 15, position.z & 15);
  }

  template <typename T> RayTraceResult<T> planeLineCollision(Plane<T> plane, Vec3<T> lineBegin, Vec3<T> lineEnd) {
    RayTraceResult<T> result;
    Vec3<T> N = math::getNormal(plane);         //Normal to plane

    Vec3<T> CA = plane.A - lineBegin;     //Vector from A to lineBegin
    Vec3<T> CV = lineEnd - lineBegin;     //Vector from lineEnd to lineBegin

    T CN = math::dotProduct(CA, N);             //Distance between plane and line
    if(CN <= 0.0) {
      return result;                             //If distance zero return
    }

    T CM = math::dotProduct(CV, N);
    if(abs(CM) < 0.0001) {
      return result;
    }

    T K = CN / CM;
    if(K < 0.0 || K > 1.0) {
      return result;                       //if k < 0 or k > 1 line does not reach plane
    }

    result.pos = CV * K + lineBegin - plane.A + Vec3<T>(abs(N.y) + abs(N.z), 0.0, 0.0);                     //Collision point on plane
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
}