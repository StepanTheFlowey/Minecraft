#pragma once

#include <unordered_map>

#include "types.hpp"
#include "vec2.hpp"
#include "aabb3.hpp"
#include "math.hpp"
#include "chunk.hpp"

using regionPos_t = int16_t;
using RegionPos = Vec2<regionPos_t>;
using RegionAabb = Aabb3<regionPos_t>;

inline ChunkPos getChunkPosFromBlock(const BlockPos);

inline SmallPos getChunkPosInRegion(const ChunkPos);

inline uint16_t getChunkIndexFromPos(const SmallPos);

inline SmallPos getPosFromChunkIndex(const uint16_t index);

class Player;

class Region {
  Chunk* chunk_[4096];
  World* worldIn_ = 0;
  RegionAabb aabb_;
  RegionPos position_;
public:

  //Default constructor
  Region();

  //Default destructor
  ~Region();

  //Takes block pointer from native grid
  NODISCARD const Block* getBlock(const SmallPos) const;

  //
  void setBlock(const SmallPos, Block*);

  //Check for chunk exist
  bool hasChunk(const SmallPos) const;

  //Takes chunk pointer from native grid
  NODISCARD Chunk* getChunk(const SmallPos) const;

  //
  void createChunk(const SmallPos);

  //
  void destroyChunk(const SmallPos);

  //Assign region position
  void setPosition(const RegionPos);

  //Takes region position
  NODISCARD const RegionPos& getPosition() const;

  //Takes region position
  NODISCARD const RegionAabb& getAabb() const;

  //Assign world in pointer
  void setWorldIn(World*);

  //Draws underlying chunks
  void draw() const;

  friend Player;
};

#include "region.inl"