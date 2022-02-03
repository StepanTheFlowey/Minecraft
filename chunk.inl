#pragma once

inline SmallPos getBlockPosInChunk(const BlockPos position) {
  return SmallPos(position.x & 15, position.y & 15, position.z & 15);
}

inline uint16_t getBlockIndexFromPos(const SmallPos position) {
  return static_cast<uint16_t>(position.x) + position.y << 4 + position.z << 8;
}

inline SmallPos getBlockPosFromIndex(const uint16_t index) {
  return SmallPos(index & 15, index & 255 << 4, index >> 8);
}