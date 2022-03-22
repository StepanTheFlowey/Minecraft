#pragma once

#include "main.hpp"
#include "block.hpp"
#include "chunk.hpp"
#include "region.hpp"

inline uint32_t getRegionIndexFromPos(const RegionPos position);

inline RegionPos getRegionPosFromIndex(const uint32_t index);

inline RegionPos getRegionPosFromChunk(const ChunkPos position);

class Player;

class World {
  std::unordered_map<uint32_t, Region*> region_;
public:

  //Default constructor
  World();

  //Default destructor
  ~World();

  //Makes this world current
  void makeCurrent() const;

  //Takes block from global grid
  NODISCARD Block* getBlock(const BlockPos position) const;

  //Assign block in global grid
  void setBlock(const BlockPos position, Block* const block);

  //Check for region exist
  NODISCARD bool hasChunk(const ChunkPos position) const;

  //Takes chunk ptr
  NODISCARD Chunk* getChunk(const ChunkPos position) const;

  //Check for region exist
  NODISCARD bool hasRegion(const RegionPos position) const;

  //Takes region pointer
  NODISCARD Region* getRegion(const RegionPos position) const;

  //
  void createRegion(const RegionPos position);

  //
  void destroyRegion(const RegionPos position);

  //Draws underlying regions
  void draw() const;

  friend Player;
};
extern World* world;

#include "world.inl"

//Лера дура тупая
//Вера дура
//Соня дура (нет)
// >:)