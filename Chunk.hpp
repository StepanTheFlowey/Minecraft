#pragma once

#include "main.hpp"
#include "Vec3.hpp"
#include "Math.hpp"
#include "Block.hpp"

using chunkPos_t = int32_t;           //Absolute chunk position
using ChunkPos = Vec3<chunkPos_t>;
using ChunkAabb = Aabb3<chunkPos_t>;

inline SmallPos getBlockPosInChunk(const BlockPos& position);
inline uint16_t getBlockIndexFromPos(const SmallPos& position);
inline SmallPos getBlockPosFromIndex(const uint16_t index);

class World;
class Player;

class Chunk {
public:

  //Default constructor
  Chunk();

  //Default destructor
  ~Chunk();

  //Takes block
  NODISCARD Block* getBlock(const SmallPos& position) const;

  //Sets block
  void setBlock(const SmallPos& position, Block* const block);

  //Sets chunk position
  void setPosition(const ChunkPos& position);

  //Returns chunk position
  NODISCARD const ChunkPos& getPosition() const;

  //Returns chunk AABB
  NODISCARD const ChunkAabb& getAabb() const;

  //Calculates blocks edge render
  void updateBlocksRender();

  //Draws blocks
  void draw() const;
protected:

  Block* block_[4096]{};

  ChunkAabb aabb_;
  ChunkPos position_;
  BlockRenderer* renderer_;

  friend Player;
};

#include "Chunk.inl"
