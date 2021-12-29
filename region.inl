#pragma once

inline SmallPos getChunkPosInRegion(ChunkPos position) {
  return SmallPos(position.x & 15, position.y & 15, position.z & 15);
}

inline RegionPos getRegionPosFromChunk(ChunkPos position) {
  return RegionPos(position.x >> 4, position.z >> 4);
}
