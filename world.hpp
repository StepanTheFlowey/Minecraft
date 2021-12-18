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

  void test();

  bool hasRegion(RegionPos position);

  std::shared_ptr<Region> getRegion(RegionPos position);

  bool hasChunk(ChunkPos position);

  std::shared_ptr<Chunk> getChunk(ChunkPos position);

  bool hasBlock();

  BlockRenderInfo getBlock(BlockPos position);

  void setBlock(BlockPos position, BlockRenderInfo block);

  constexpr auto& getData();

  void draw();
};