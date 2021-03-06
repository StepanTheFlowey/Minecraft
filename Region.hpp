#pragma once

#include <unordered_map>

#include "main.hpp"
#include "Vec2.hpp"
#include "Aabb3.hpp"
#include "Math.hpp"
#include "Chunk.hpp"

using regionPos_t = int16_t;            //Absolute region pos
using RegionPos = Vec2<regionPos_t>;
using RegionAabb = Aabb3<regionPos_t>;

inline ChunkPos getChunkPosFromBlock(const BlockPos& position);
inline SmallPos getChunkPosInRegion(const ChunkPos& position);
inline uint16_t getChunkIndexFromPos(const SmallPos& position);
inline SmallPos getPosFromChunkIndex(const uint16_t index);

class Player;

class Region {
public:

  //Default constructor
  Region();

  //Default destructor
  ~Region();

  //Takes block pointer from native grid
  NODISCARD const Block* getBlock(const SmallPos) const;

  //Sets block
  void setBlock(const SmallPos position, Block* const block);

  //Takes chunk pointer from native grid
  NODISCARD Chunk* getChunk(const SmallPos position) const;

  //Creates chunk
  void createChunk(const SmallPos position);

  //Destroys chunk
  void destroyChunk(const SmallPos position);

  //Sets region position
  void setPosition(const RegionPos position);

  //Takes region position
  NODISCARD const RegionPos& getPosition() const;

  //Takes region position
  NODISCARD const RegionAabb& getAabb() const;

  //Draws underlying chunks
  void draw() const;

  friend Player;
protected:

  Chunk* chunk_[4096];
  RegionAabb aabb_;
  RegionPos position_;
};

#include "Region.inl"
