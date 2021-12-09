#pragma once
#include "types.hpp"
#include <cmath>

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
}