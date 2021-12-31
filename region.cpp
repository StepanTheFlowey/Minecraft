#pragma once

#include "region.hpp"

#include "world.hpp"

Region::Region() {
#ifdef DEBUG
  std::wcout << L"Region(): Constructor" << std::endl;
#endif // DEBUG
  for(uint8_t i = 0; i < 8; i++) {
    for(uint8_t j = 0; j < 8; j++) {
      chunk_[i][0][j].reset(new Chunk);
      ñhunk_[i][0][j]->setWorldIn(worldIn_);
      chunk_[i][0][j]->setPosition(ChunkPos(i, 0, j));
      chunk_[i][0][j]->computeBlocksEdgeRender();
    }
  }
}

Region::~Region() {
#ifdef DEBUG
  std::wcout << L"~Region(): Destructor" << std::endl;
#endif // DEBUG
}

bool Region::hasChunkWorld(ChunkPos position) {
  return hasChunkNative(getChunkPosInRegion(position));
}

bool Region::hasChunkNative(SmallPos position) {
  if(chunk_.find(position.x) == chunk_.end()) {
    return false;
  }
  if(chunk_[position.x].find(position.y) == chunk_[position.x].end()) {
    return false;
  }
  if(chunk_[position.x][position.y].find(position.z) == chunk_[position.x][position.y].end()) {
    return false;
  }
  return true;
}

const std::shared_ptr<Chunk> Region::getChunkNative(SmallPos position) {
  return chunk_[position.x][position.y][position.z];
}

const std::shared_ptr<Chunk> Region::getChunkWorld(ChunkPos position) {
  return getChunkNative(getChunkPosInRegion(position));
}

const BlockRenderInfo Region::getBlockNative(BlockPos position) {
  return getChunkWorld(getChunkPosFromBlock(position))->getBlockWorld(position);
}

//const BlockRenderInfo Region::getBlockWorld(BlockPos position) {
  //return getBlockNative(getBlock);
//}

void Region::setPosition(RegionPos position) {
  position_ = position;
  aabb_.min.x = position.x;
  aabb_.min.y = 0;
  aabb_.min.z = position.y;
  aabb_.max.x = position.x + 16;
  aabb_.max.y = 256;
  aabb_.max.z = position.y + 16;

  for(auto& [iKey, iVal] : chunk_) {
    for(auto& [jKey, jVal] : iVal) {
      for(auto& [kKey, kVal] : jVal) {
        kVal->setPosition(ChunkPos(position_.x, 0, position_.y) + SmallPos(iKey, jKey, kKey));
      }
    }
  }
}

const RegionPos& Region::getPosition() const {
  return position_;
}

const RegionAabb& Region::getAabb() const {
  return aabb_;
}

void Region::setWorldIn(std::weak_ptr<World> worldIn) {
  worldIn_ = worldIn;

  for(auto& [iKey, iVal] : chunk_) {
    for(auto& [jKey, jVal] : iVal) {
      for(auto& [kKey, kVal] : jVal) {
        kVal->setWorldIn(worldIn_);
      }
    }
  }
}

void Region::draw() const {
  for(auto& [iKey, iVal] : chunk_) {
    for(auto& [jKey, jVal] : iVal) {
      for(auto& [kKey, kVal] : jVal) {
        kVal->draw();
      }
    }
  }
}
