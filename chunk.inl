#pragma once

inline SmallPos getBlockPosInChunk(BlockPos position) {
  return SmallPos(position.x & 15, position.y & 15, position.z & 15);
}

inline ChunkPos getChunkPosFromBlock(BlockPos position) {
  return ChunkPos(position.x >> 4, position.y >> 4, position.z >> 4);
}