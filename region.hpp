#pragma once
#include "types.hpp"
#include "chunk.hpp"

#include <unordered_map>

class Region {
  std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::shared_ptr<Chunk>>>> chunk_;
  std::weak_ptr<World> worldIn_;
  RegionAabb aabb_;
  RegionPos position_;
public:
  Region() {
#ifdef DEBUG
    std::wcout << L"Region(): Constructor" << std::endl;
#endif // DEBUG
    chunk_[0][0][0].reset(new Chunk);
    chunk_[0][0][0]->setPosition(ChunkPos(0, 0, 0));
  }

  ~Region() {
#ifdef DEBUG
    std::wcout << L"~Region(): Destructor" << std::endl;
#endif // DEBUG
  }

  bool hasChunkWorld(ChunkPos position) {
    return hasChunkNative(math::getChunkPosInRegion(position));
  }

  bool hasChunkNative(SmallPos position) {
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

  std::shared_ptr<Chunk> getChunkNative(SmallPos position) {
    return chunk_[position.x][position.y][position.z];
  }

  std::shared_ptr<Chunk> getChunkWorld(ChunkPos position) {
    return getChunkNative(math::getChunkPosInRegion(position));
  }

  BlockRenderInfo getBlockNative(BlockPos position) {
    return getChunkWorld(math::getChunkPosFromBlock(position))->getBlockWorld(position);
  }

  BlockRenderInfo getBlockWorld(BlockPos position) {
    //return getBlockNative(getBlock);
  }

  void setPosition(RegionPos position) {
    position_ = position;
    aabb_.minX = position.x;
    aabb_.minY = 0;
    aabb_.minZ = position.y;
    aabb_.maxX = position.x + 16;
    aabb_.maxY = 256;
    aabb_.maxZ = position.y + 16;

    for(auto &[iKey, iVal] : chunk_) {
      for(auto &[jKey, jVal] : iVal) {
        for(auto &[kKey, kVal] : jVal) {
          kVal->setPosition(ChunkPos(position_.x, 0, position_.y) + SmallPos(iKey, jKey, kKey));
        }
      }
    }
  }

  RegionPos &getPosition() {
    return position_;
  }

  RegionAabb &getAabb() {
    return aabb_;
  }

  void setWorldIn(std::weak_ptr<World> worldIn) {
    worldIn_ = worldIn;

    for(auto &[iKey, iVal] : chunk_) {
      for(auto &[jKey, jVal] : iVal) {
        for(auto &[kKey, kVal] : jVal) {
          kVal->setWorldIn(worldIn_);
        }
      }
    }
  }

  auto &getData() {
    return chunk_;
  }

  void draw() const {
    for(auto &[iKey, iVal] : chunk_) {
      for(auto &[jKey, jVal] : iVal) {
        for(auto &[kKey, kVal] : jVal) {
          kVal->draw();
        }
      }
    }
  }
};