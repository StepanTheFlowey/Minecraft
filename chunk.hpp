#pragma once

#include "main.hpp"
#include "vec3.hpp"
#include "math.hpp"
#include "block.hpp"
#include "blockRenderer.hpp"

using chunkPos_t = int32_t;
using ChunkPos = Vec3<chunkPos_t>;
using ChunkAabb = Aabb3<chunkPos_t>;

inline SmallPos getBlockPosInChunk(const BlockPos);

inline uint16_t getBlockIndexFromPos(const SmallPos);

inline SmallPos getBlockPosFromIndex(const uint16_t index);

class World;
class Player;

class Chunk {
  Block* block_[4096];
  World* worldIn_ = nullptr;
  ChunkAabb aabb_;
  ChunkPos position_;
  BlockRenderer renderer_;
public:

  //Default constructor
  Chunk();

  //Default destructor
  ~Chunk();

  //Takes block
  NODISCARD Block* getBlock(const SmallPos) const;

  //Sets block
  void setBlock(const SmallPos, Block*);

  //Sets chunk position
  void setPosition(const ChunkPos);

  //Returns chunk position
  NODISCARD const ChunkPos& getPosition() const;

  //Returns chunk AABB
  NODISCARD const ChunkAabb& getAabb() const;

  //Sets world in ptr
  void setWorldIn(World* const worldIn);

  //Calculates blocks edge render
  void computeBlocksEdgeRender();

  //Draws blocks
  void draw() const;

  friend Player;
};

#include "chunk.inl"
