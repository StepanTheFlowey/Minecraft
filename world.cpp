#pragma once

#include "world.hpp"

#include "math.hpp"

World::World() {
#ifdef DEBUG
  std::wcout << L"World(): Constructor" << std::endl;
#endif // DEBUG
}

World::~World() {
#ifdef DEBUG
  std::wcout << L"~World(): Destructor" << std::endl;
#endif // DEBUG
}

void World::test() {
  region_[0][0].reset(new Region);
  region_[0][0]->setPosition(RegionPos(0, 0));
  region_[0][0]->setWorldIn(weak_from_this());
}

bool World::hasRegion(RegionPos position) {
  if(region_.find(position.x) == region_.end()) {
    return false;
  }
  if(region_[position.x].find(position.y) == region_[position.x].end()) {
    return false;
  }
  return true;
}

std::shared_ptr<Region> World::getRegion(RegionPos position) {
  return region_[position.x][position.y];
}

bool World::hasChunk(ChunkPos position) {
  RegionPos regionPos = getRegionPosFromChunk(position);
  if(!hasRegion(regionPos)) {
    return false;
  }
  return getRegion(regionPos)->hasChunkWorld(position);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos position) {
  RegionPos regionPos = getRegionPosFromChunk(position);
  return getRegion(regionPos)->getChunkWorld(position);
}

BlockRenderInfo World::getBlock(BlockPos position) {
  ChunkPos chunkPos =getChunkPosFromBlock(position);
  RegionPos regionPos = getRegionPosFromChunk(chunkPos);
  return getRegion(regionPos)->getChunkWorld(chunkPos)->getBlockWorld(position);
}

void World::setBlock(BlockPos position, BlockRenderInfo block) {
  ChunkPos chunkPos = getChunkPosFromBlock(position);
  RegionPos regionPos = getRegionPosFromChunk(chunkPos);
  getRegion(regionPos)->getChunkWorld(chunkPos)->setBlockWorld(position, block);
}

void World::draw() {
  for(auto& [iKey, iVal] : region_) {
    for(auto& [jKey, jVal] : iVal) {
      jVal->draw();
    }
  }
}