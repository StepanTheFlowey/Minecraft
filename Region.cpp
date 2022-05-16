#include "Region.hpp"

#include "World.hpp"

Region::Region() {
  debug(L"Region()");
  for(uint16_t i = 0; i < 4096; ++i) chunk_[i] = nullptr;
}

Region::~Region() {
  debug(L"~Region()");
  for(uint16_t i = 0; i < 4096; ++i) {
    if(chunk_[i] != nullptr) {
      delete chunk_[i];
      chunk_[i] = nullptr;
    }
  }
}

const Block* Region::getBlock(const SmallPos position) const {
  return getChunk(getChunkPosInRegion(getChunkPosFromBlock(position)))->getBlock(position);
}

void Region::setBlock(const SmallPos position, Block* const block) {
  getChunk(getChunkPosInRegion(getChunkPosFromBlock(position)))->setBlock(getBlockPosInChunk(position), block);
}

Chunk* Region::getChunk(const SmallPos position) const {
  return chunk_[getChunkIndexFromPos(position)];
}

void Region::createChunk(const SmallPos position) {
  uint16_t index = getChunkIndexFromPos(position);
  if(chunk_[index] != nullptr) {
    throw std::logic_error("chunk already created");
  }
  chunk_[index] = new Chunk;
}

void Region::destroyChunk(const SmallPos position) {
  uint16_t index = getChunkIndexFromPos(position);
  if(chunk_[index] == nullptr) {
    throw std::logic_error("chunk not created");
  }
  delete chunk_[index];
}

void Region::setPosition(const RegionPos position) {
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

void Region::draw() const {
  for(auto& i : chunk_) {
    if(i != nullptr) {
      i->draw();
    }
  }
}
