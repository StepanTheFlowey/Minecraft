#include "Chunk.hpp"

#include "World.hpp"

Chunk::Chunk() {
  debug(L"Chunk()");
  for(uint_fast16_t i = 0; i < 4096; ++i) {
    if(rand() % 2) {
      block_[i] = nullptr;
    }
    else {
      block_[i] = createBlock<Block>();
      block_[i]->id = 1;
    }
  }
}

Chunk::~Chunk() {
  debug(L"~Chunk()");
  for(uint_fast16_t i = 0; i < 4096; ++i) {
    if(block_[i] != nullptr) {
      delete block_[i];
    }
  }
}

Block* Chunk::getBlock(const SmallPos position) const {
  return block_[getBlockIndexFromPos(position)];
}

void Chunk::setBlock(const SmallPos position, Block* const block) {
  const uint_fast16_t index = getBlockIndexFromPos(position);
  if(block_[index] != nullptr) {
    delete block_[index];
  }
    block_[index] = block;
}

void Chunk::setPosition(const ChunkPos position) {
  position_ = position;
  aabb_.min = position_ * 16;
  aabb_.max = (position_ + 1) * 16;
}

const ChunkPos& Chunk::getPosition() const {
  return position_;
}

const ChunkAabb& Chunk::getAabb() const {
  return aabb_;
}

void Chunk::updateBlocksRender() {
  const Chunk* upChunk = nullptr;
  if(world->hasChunk(position_ + ChunkPos(0, 1, 0))) {
    upChunk = world->getChunk(position_ + ChunkPos(0, 1, 0));
  }
  const Chunk* downChunk = nullptr;
  if(world->hasChunk(position_ - ChunkPos(0, 1, 0))) {
    downChunk = world->getChunk(position_ - ChunkPos(0, 1, 0));
  }
  const Chunk* northChunk = nullptr;
  if(world->hasChunk(position_ - ChunkPos(1, 0, 0))) {
    northChunk = world->getChunk(position_ - ChunkPos(1, 0, 0));
  }
  const Chunk* southChunk = nullptr;
  if(world->hasChunk(position_ + ChunkPos(1, 0, 0))) {
    southChunk = world->getChunk(position_ + ChunkPos(1, 0, 0));
  }
  const Chunk* westChunk = nullptr;
  if(world->hasChunk(position_ + ChunkPos(0, 0, 1))) {
    westChunk = world->getChunk(position_ + ChunkPos(0, 0, 1));
  }
  const Chunk* eastChunk = nullptr;
  if(world->hasChunk(position_ - ChunkPos(0, 0, 1))) {
    eastChunk = world->getChunk(position_ - ChunkPos(0, 0, 1));
  }


  const BlockPos blockPos = position_ * 16;

  VertexBuffer<BlockVertex> vertexBuffer;
  Block* block;

  for(uint8_t i = 0; i < 16; ++i) {
    for(uint8_t j = 0; j < 16; ++j) {
      for(uint8_t k = 0; k < 16; ++k) {
        block = block_[getBlockIndexFromPos(SmallPos(i, j, k))];
        if(block == nullptr) {
          continue;
        }
        if(block->id == 0) {
          block->side = Side::None;
          continue;
        }
        block->side = Side::Null;

        if(j == 15) {
          if(upChunk) {
            block->side |= upChunk->getBlock(BlockPos(i, 0, k))->id == 0 ? Side::Up : Side::Null;
          }
        }
        else {
          block->side |= getBlock(BlockPos(i, j + 1, k))->id == 0 ? Side::Up : Side::Null;
        }

        if(j == 0) {
          if(downChunk) {
            block->side |= downChunk->getBlock(BlockPos(i, 15, k))->id == 0 ? Side::Down : Side::Null;
          }
        }
        else {
          block->side |= getBlock(BlockPos(i, j - 1, k))->id == 0 ? Side::Down : Side::Null;
        }

        if(i == 0) {
          if(northChunk) {
            block->side |= northChunk->getBlock(BlockPos(15, j, k))->id == 0 ? Side::North : Side::Null;
          }
        }
        else {
          block->side |= getBlock(BlockPos(i - 1, j, k))->id == 0 ? Side::North : Side::Null;
        }

        if(i == 15) {
          if(southChunk) {
            block->side |= southChunk->getBlock(BlockPos(0, j, k))->id == 0 ? Side::South : Side::Null;
          }
        }
        else {
          block->side |= getBlock(BlockPos(i + 1, j, k))->id == 0 ? Side::South : Side::Null;
        }

        if(k == 15) {
          if(westChunk) {
            block->side |= westChunk->getBlock(BlockPos(i, j, 0))->id == 0 ? Side::West : Side::Null;
          }
        }
        else {
          block->side |= getBlock(BlockPos(i, j, k + 1))->id == 0 ? Side::West : Side::Null;
        }

        if(k == 0) {
          if(eastChunk) {
            block->side |= eastChunk->getBlock(BlockPos(i, j, 15))->id == 0 ? Side::East : Side::Null;
          }
        }
        else {
          block->side |= getBlock(BlockPos(i, j, k - 1))->id == 0 ? Side::East : Side::Null;
        }

        if(block->side == Side::Full) {
          block->side = Side::All;
        }
        else if(block->side == Side::Null) {
          block->side = Side::None;
        }
      }
    }
  }
  renderer_.update(vertexBuffer);
}

void Chunk::draw() const {
  glPushMatrix();
  glTranslated(
    static_cast<GLdouble>(position_.x * 16.0),
    static_cast<GLdouble>(position_.y * 16.0),
    static_cast<GLdouble>(position_.z * 16.0)
  );
  renderer_.draw();
  glPopMatrix();

#ifdef DEBUG
  aabb_.draw(0.25F);
#endif // DEBUG
}
