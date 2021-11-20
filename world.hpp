#pragma once
#include "types.hpp"
#include "region.hpp"

class World : public std::enable_shared_from_this<World> {
  std::unordered_map<regionPos_t, std::unordered_map<regionPos_t, std::shared_ptr<Region>>> region_;
public:
  World() {
#ifdef DEBUG
    std::wcout << L"World(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~World() {
#ifdef DEBUG
    std::wcout << L"~World(): Destructor" << std::endl;
#endif // DEBUG
  }

  void test() {
    region_[0][0].reset(new Region);
    region_[0][0]->setPosition(RegionPos(0, 0));
    region_[0][0]->setWorldIn(weak_from_this());
    region_[0][0]->getChunkNative(SmallPos(0, 0, 0))->computeBlocksEdgeRender();
  }

  bool hasRegion(RegionPos position) {
    if(region_.find(position.x) == region_.end()) {
      return false;
    }
    if(region_[position.x].find(position.y) == region_[position.x].end()) {
      return false;
    }
    return true;
  }

  std::shared_ptr<Region> getRegion(RegionPos position) {
    return region_[position.x][position.y];
  }

  bool hasChunk(ChunkPos position) {
    RegionPos regionPos = getRegionPosFromChunk(position);
    if(!hasRegion(regionPos)) {
      return false;
    }
    return getRegion(regionPos)->hasChunkWorld(position);
  }

  std::shared_ptr<Chunk> getChunk(ChunkPos position) {
    RegionPos regionPos = getRegionPosFromChunk(position);
    return getRegion(regionPos)->getChunkWorld(position);
  }

  bool hasBlock() {
    //TODO: World::hasBlock()
  }

  BlockRenderInfo getBlock(BlockPos position) {
    ChunkPos chunkPos = getChunkPosFromBlock(position);
    RegionPos regionPos = getRegionPosFromChunk(chunkPos);
    return getRegion(regionPos)->getChunkWorld(chunkPos)->getBlockWorld(position);
  }

  void setBlock(BlockPos position, BlockRenderInfo block) {
    ChunkPos chunkPos = getChunkPosFromBlock(position);
    RegionPos regionPos = getRegionPosFromChunk(chunkPos);
    getRegion(regionPos)->getChunkWorld(chunkPos)->setBlockWorld(position, block);
  }

  constexpr auto &getData() {
    return region_;
  }

  void draw() {
    for(auto &[iKey, iVal] : region_) {
      for(auto &[jKey, jVal] : iVal) {
        jVal->draw();
      }
    }
  }
};


void Chunk::computeBlocksEdgeRender() {
  std::shared_ptr<World> world=getWorldPtr();

  std::shared_ptr<Chunk> upChunk = nullptr;
  if(world->hasChunk(position_ + ChunkPos(0, 1, 0))) {
    upChunk = world->getChunk(position_ + ChunkPos(0, 1, 0));
  }
  std::shared_ptr<Chunk> downChunk = nullptr;
  if(world->hasChunk(position_ - ChunkPos(0, 1, 0))) {
    downChunk = world->getChunk(position_ - ChunkPos(0, 1, 0));
  }
  std::shared_ptr<Chunk> northChunk = nullptr;
  if(world->hasChunk(position_ - ChunkPos(1, 0, 0))) {
    northChunk = world->getChunk(position_ - ChunkPos(1, 0, 0));
  }
  std::shared_ptr<Chunk> southChunk = nullptr;
  if(world->hasChunk(position_ + ChunkPos(1, 0, 0))) {
    southChunk = world->getChunk(position_ + ChunkPos(1, 0, 0));
  }
  std::shared_ptr<Chunk> westChunk = nullptr;
  if(world->hasChunk(position_ + ChunkPos(0, 0, 1))) {
    westChunk = world->getChunk(position_ + ChunkPos(0, 0, 1));
  }
  std::shared_ptr<Chunk> eastChunk = nullptr;
  if(world->hasChunk(position_ - ChunkPos(0, 0, 1))) {
    eastChunk = world->getChunk(position_ - ChunkPos(0, 0, 1));
  }

  BlockPos blockPos = position_ * 16;

  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        BlockRenderInfo &block = getBlockNative(BlockPos(i, j, k));
        if(block.blockId == 0) {
          bitWrite(block.sideRender, 1, 1);
          continue;
        }
        block.sideRender = 0b11111100;

        if(j == 15) {
          if(upChunk) {
            bitWrite(block.sideRender, 2, upChunk->getBlockNative(BlockPos(i, 0, k)).blockId == 0);
          }
        }
        else {
          bitWrite(block.sideRender, 2, getBlockNative(BlockPos(i, j + 1, k)).blockId == 0);
        }

        if(j == 0) {
          if(downChunk) {
            bitWrite(block.sideRender, 3, downChunk->getBlockNative(BlockPos(i, 15, k)).blockId == 0);
          }
        }
        else {
          bitWrite(block.sideRender, 3, getBlockNative(BlockPos(i, j - 1, k)).blockId == 0);
        }

        if(i == 0) {
          if(northChunk) {
            bitWrite(block.sideRender, 4, northChunk->getBlockNative(BlockPos(15, j, k)).blockId == 0);
          }
        }
        else {
          bitWrite(block.sideRender, 4, getBlockNative(BlockPos(i - 1, j, k)).blockId == 0);
        }

        if(i == 15) {
          if(southChunk) {
            bitWrite(block.sideRender, 5, southChunk->getBlockNative(BlockPos(0, j, k)).blockId == 0);
          }
        }
        else {
          bitWrite(block.sideRender, 5, getBlockNative(BlockPos(i + 1, j, k)).blockId == 0);
        }

        if(k == 15) {
          if(westChunk) {
            bitWrite(block.sideRender, 6, westChunk->getBlockNative(BlockPos(i, j, 0)).blockId == 0);
          }
        }
        else {
          bitWrite(block.sideRender, 6, getBlockNative(BlockPos(i, j, k + 1)).blockId == 0);
        }

        if(k == 0) {
          if(eastChunk) {
            bitWrite(block.sideRender, 7, eastChunk->getBlockNative(BlockPos(i, j, 15)).blockId == 0);
          }
        }
        else {
          bitWrite(block.sideRender, 7, getBlockNative(BlockPos(i, j, k - 1)).blockId == 0);
        }

        bitWrite(block.sideRender, 0, (
          bitRead(block.sideRender, 2) &&
          bitRead(block.sideRender, 3) &&
          bitRead(block.sideRender, 4) &&
          bitRead(block.sideRender, 5) &&
          bitRead(block.sideRender, 6) &&
          bitRead(block.sideRender, 7)));
        bitWrite(block.sideRender, 1, !(
          bitRead(block.sideRender, 2) ||
          bitRead(block.sideRender, 3) ||
          bitRead(block.sideRender, 4) ||
          bitRead(block.sideRender, 5) ||
          bitRead(block.sideRender, 6) ||
          bitRead(block.sideRender, 7)));
      }
    }
  }
}