#pragma once

inline ChunkPos getChunkPosFromBlock(const BlockPos position) {
  return ChunkPos(position.x >> 4, position.y >> 4, position.z >> 4);
}

inline SmallPos getChunkPosInRegion(const ChunkPos position) {
  return SmallPos(position.x & 15, position.y & 15, position.z & 15);
}

inline uint16_t getChunkIndexFromPos(const SmallPos position) {
  return static_cast<uint16_t>(position.x)  + position.y * 16 + position.z * 256;
}

inline SmallPos getPosFromChunkIndex(const uint16_t index) {
  return SmallPos(index & 15, index & 255 >> 4, index >> 8);
}