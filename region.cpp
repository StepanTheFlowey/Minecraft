#include "region.hpp"

#include "world.hpp"

Region::Region() {
#ifdef DEBUG
  std::wcout << L"Region()" << std::endl;
#endif // DEBUG
}

Region::~Region() {
#ifdef DEBUG
  std::wcout << L"~Region()" << std::endl;
#endif // DEBUG
}

void Region::test() {
  for(uint8_t i = 0; i < 8; i++) {
    for(uint8_t j = 0; j < 8; j++) {
      for(uint8_t k = 0; k < 8; k++) {
        chunk_[i][j][k].reset(new Chunk);
        chunk_[i][j][k]->setWorldIn(worldIn_);
        chunk_[i][j][k]->setPosition(ChunkPos(i, j, k));
      }
    }
  }

  for(uint8_t i = 0; i < 8; i++) {
    for(uint8_t j = 0; j < 8; j++) {
      for(uint8_t k = 0; k < 8; k++) {
        chunk_[i][j][k]->computeBlocksEdgeRender();
      }
    }
  }
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
  aabb_.max.x = position.x + 256;
  aabb_.max.y = 256;
  aabb_.max.z = position.y + 256;
}

const RegionPos& Region::getPosition() const {
  return position_;
}

const RegionAabb& Region::getAabb() const {
  return aabb_;
}

void Region::setWorldIn(std::weak_ptr<World> worldIn) {
  worldIn_ = worldIn;
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
