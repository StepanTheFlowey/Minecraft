#pragma once

inline uint32_t getRegionIndexFromPos(const RegionPos position) {
  return position.x + position.y * 65536;
}

inline RegionPos getRegionPosFromIndex(const uint32_t position) {

}

inline RegionPos getRegionPosFromChunk(const ChunkPos position) {
  return RegionPos(position.x >> 4, position.z >> 4);
}