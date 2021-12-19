#pragma once

#include "types.hpp"
#include "region.hpp"

class World: public std::enable_shared_from_this<World> {
  std::unordered_map<regionPos_t, std::unordered_map<regionPos_t, std::shared_ptr<Region>>> region_;
public:

  //Default constructor
  World();

  //Default destructor
  ~World();

  //Лера дура
  void test();

  //Check for region exist
  bool hasRegion(RegionPos position);

  //Takes region ptr
  std::shared_ptr<Region> getRegion(RegionPos position);

  //Check for region exist
  bool hasChunk(ChunkPos position);

  //Takes chunk ptr
  std::shared_ptr<Chunk> getChunk(ChunkPos position);
  
  //wtf
  bool hasBlock();

  //wtf
  BlockRenderInfo getBlock(BlockPos position);

  //wtf
  void setBlock(BlockPos position, BlockRenderInfo block);

  //лера опять дура
  constexpr auto& getData();

  //Draws region
  void draw();
};