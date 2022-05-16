#pragma once

inline uint32_t getRegionIndexFromPos(const RegionPos position) {
  return position.x + (position.y << 16);
}

inline RegionPos getRegionPosFromIndex(const uint32_t position) {
  return RegionPos(position % 16, position >> 4);
}

inline RegionPos getRegionPosFromChunk(const ChunkPos position) {
  return RegionPos(position.x >> 4, position.z >> 4);
}
