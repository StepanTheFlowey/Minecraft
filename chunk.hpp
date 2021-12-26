#pragma once

#include "types.hpp"
#include "vec3.hpp"
#include "math.hpp"
#include "block.hpp"

using chunkPos_t = int32_t;
using ChunkPos = Vec3<chunkPos_t>;
using ChunkAabb = Aabb3<chunkPos_t>;

inline SmallPos getBlockPosInChunk(BlockPos);

inline ChunkPos getChunkPosFromBlock(BlockPos);

inline SmallPos getBlockPosInChunk(BlockPos position) {
  return SmallPos(position.x & 15, position.y & 15, position.z & 15);
}

inline ChunkPos getChunkPosFromBlock(BlockPos position) {
  return ChunkPos(position.x >> 4, position.y >> 4, position.z >> 4);
}

class World;

class Chunk {
  BlockRenderInfo block_[16][16][16];
  std::weak_ptr<World> worldIn_;
  ChunkAabb aabb_;
  ChunkPos position_;
public:

  //Default constructor
  Chunk();

  //Default destructor
  ~Chunk();

  //Takes block from native chunk grid
  BlockRenderInfo& getBlockNative(SmallPos position);

  //Takes block from world grid
  BlockRenderInfo& getBlockWorld(BlockPos position);

  //Sets block in native chunk`s grid
  void setBlockNative(BlockPos position, BlockRenderInfo block);

  //Sets block in world grid
  void setBlockWorld(BlockPos position, BlockRenderInfo block);

  //Sets chunk position
  void setPosition(ChunkPos position);

  //Returns chunk position
  ChunkPos& getPosition();

  //Returns chunk AABB
  ChunkAabb& getAabb();

  //Sets world in ptr
  void setWorldIn(std::weak_ptr<World> worldIn);

  //Calculates blocks edge render
  void computeBlocksEdgeRender();

  //Draws blocks
  void draw() const;
private:

  //Makes shared pointer from weak one
  std::shared_ptr<World> getWorldPtr();
};