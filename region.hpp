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

inline SmallPos getChunkPosInRegion(ChunkPos);

inline RegionPos getRegionPosFromChunk(ChunkPos);

class Player;

class Region {
  std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::shared_ptr<Chunk>>>> chunk_;
  std::weak_ptr<World> worldIn_;
  RegionAabb aabb_;
  RegionPos position_;
public:

  //Default constructor
  Region();

  //Default destructor
  ~Region();

  //Check for chunk exist in native grid
  bool hasChunkNative(SmallPos position);

  //Check for chunk exist in world grid
  bool hasChunkWorld(ChunkPos position);

  //Takes chunk pointer from native grid
  const std::shared_ptr<Chunk> getChunkNative(SmallPos position);

  //Takes chunk pointer from world grid
  const std::shared_ptr<Chunk> getChunkWorld(ChunkPos position);

  //
  void createChunk(SmallPos position);

  //
  void destroyChunk();

  //Takes block pointer from native grid
  const BlockRenderInfo getBlockNative(BlockPos position);

  //Takes block pointer from world grid 
  //const BlockRenderInfo getBlockWorld(BlockPos position);

  //Assign region position
  void setPosition(RegionPos position);

  //Takes region position
  const RegionPos& getPosition() const;

  //Takes region position
  const RegionAabb& getAabb() const;

  //Assign world in pointer
  void setWorldIn(std::weak_ptr<World> worldIn);

  //Draws underlying chunks
  void draw() const;

  friend Player;
};

#include "region.inl"