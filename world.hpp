#pragma once

#include "types.hpp"
#include "block.hpp"
#include "chunk.hpp"
#include "region.hpp"

class Player;

class World: public std::enable_shared_from_this<World> {
  std::unordered_map<regionPos_t, std::unordered_map<regionPos_t, std::shared_ptr<Region>>> region_;
public:

  //Default constructor
  World();

  //Default destructor
  ~World();

  //Ñreates test chunks
  void test();

  //Check for region exist
  bool hasRegion(RegionPos);

  //Takes region pointer
  std::shared_ptr<Region> getRegion(RegionPos);

  //Check for region exist
  bool hasChunk(ChunkPos);

  //Takes chunk ptr
  std::shared_ptr<Chunk> getChunk(ChunkPos);

  //Takes block from global grid
  BlockRenderInfo getBlock(BlockPos);

  //Assign block in global grid
  void setBlock(BlockPos, BlockRenderInfo);

  //Draws underlying regions
  void draw();

  friend Player;
};