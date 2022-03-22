#include "world.hpp"

#include "math.hpp"

World* world = nullptr;

World::World() {
  debug(L"World()")
}

World::~World() {
  debug(L"~World()")
}

void World::makeCurrent() const {
  world = const_cast<World*>(this);
}

Block* World::getBlock(const BlockPos position) const {
  ChunkPos chunkPos = getChunkPosFromBlock(position);
  RegionPos regionPos = getRegionPosFromChunk(chunkPos);
  return getRegion(regionPos)->getChunk(chunkPos)->getBlock(position);
}

void World::setBlock(const BlockPos position, Block* const block) {
  ChunkPos chunkPos = getChunkPosFromBlock(position);
  RegionPos regionPos = getRegionPosFromChunk(chunkPos);
  getRegion(regionPos)->getChunk(chunkPos)->setBlock(position, block);
}

bool World::hasRegion(const RegionPos position) const {
  return region_.find(getRegionIndexFromPos(position)) != region_.end();
}

Region* World::getRegion(const RegionPos position) const {
  return region_.at(getRegionIndexFromPos(position));
}

//TODO: we can return pointer to created region
void World::createRegion(const RegionPos position) {
  region_[getRegionIndexFromPos(position)];
}

void World::destroyRegion(const RegionPos position) {
  region_.erase(getRegionIndexFromPos(position));
}

bool World::hasChunk(const ChunkPos position) const {
  RegionPos regionPos = getRegionPosFromChunk(position);
  if(!hasRegion(regionPos))
    return false;
  return getRegion(regionPos)->hasChunk(position);
}

Chunk* World::getChunk(const ChunkPos position) const {
  RegionPos regionPos = getRegionPosFromChunk(position);
  return getRegion(regionPos)->getChunk(position);
}

void World::draw() const {
  for(auto& i : region_)
    i.second->draw();
}