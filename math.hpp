#pragma once

#include "types.hpp"
#include "block.hpp"
#include "chunk.hpp"
#include "region.hpp"
#include "rayTraceResult.hpp"

#define PI 3.1415926535897932384626433832795
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define DEG_TO_RAD_F 0.01745329238F

using SmallPos = Vec3<uint8_t>;

namespace math {
  template <typename T> inline Vec3<T> vectorProduct(Vec3<T> A, Vec3<T> B);

  template <typename T> inline T dotProduct(Vec3<T> A, Vec3<T> B);

  template <typename T> inline Vec3<T> getNormal(Vec3<T> A, Vec3<T> B, Vec3<T> C);

  template <typename T> inline Vec3<T> getNormal(Plane<T> plane);

  inline ChunkPos getChunkPosFromBlock(BlockPos position);

  inline RegionPos getRegionPosFromChunk(ChunkPos position);

  inline SmallPos getBlockPosInChunk(BlockPos position);

  inline SmallPos getChunkPosInRegion(ChunkPos position);

  template <typename T> RayTraceResult<T> planeLineCollision(Plane<T> plane, Vec3<T> lineBegin, Vec3<T> lineEnd);
}