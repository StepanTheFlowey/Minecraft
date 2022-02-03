#include "chunk.hpp"

#include "world.hpp"

Chunk::Chunk() {
#ifdef DEBUG
  std::wcout << L"Chunk()" << std::endl;
#endif // DEBUG
  for(uint16_t i = 0; i < 4096; i++)
    if(rand() % 2) block_[i] = nullptr;
    else {
      block_[i] = createBlock<Block>();
      block_[i]->id = 1;
    }
}

Chunk::~Chunk() {
#ifdef DEBUG
  std::wcout << L"~Chunk()" << std::endl;
#endif // DEBUG
  for(uint16_t i = 0; i < 4096; i++)
    if(block_[i] != nullptr) delete block_[i];
}

 Block* Chunk::getBlock(const SmallPos position) const {
  return block_[getBlockIndexFromPos(position)];
}

void Chunk::setBlock(const SmallPos position, Block* block) {
  const uint16_t index = getBlockIndexFromPos(position);
  if(block_[index] != nullptr)
    delete block_[index];
  if(block != nullptr)
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

void Chunk::setWorldIn(World* worldIn) {
  worldIn_ = worldIn;
}

void Chunk::computeBlocksEdgeRender() {
  const Chunk* upChunk = nullptr;
  if(worldIn_->hasChunk(position_ + ChunkPos(0, 1, 0))) {
    upChunk = worldIn_->getChunk(position_ + ChunkPos(0, 1, 0));
  }
  const Chunk* downChunk = nullptr;
  if(worldIn_->hasChunk(position_ - ChunkPos(0, 1, 0))) {
    downChunk = worldIn_->getChunk(position_ - ChunkPos(0, 1, 0));
  }
  const Chunk* northChunk = nullptr;
  if(worldIn_->hasChunk(position_ - ChunkPos(1, 0, 0))) {
    northChunk = worldIn_->getChunk(position_ - ChunkPos(1, 0, 0));
  }
  const Chunk* southChunk = nullptr;
  if(worldIn_->hasChunk(position_ + ChunkPos(1, 0, 0))) {
    southChunk = worldIn_->getChunk(position_ + ChunkPos(1, 0, 0));
  }
  const Chunk* westChunk = nullptr;
  if(worldIn_->hasChunk(position_ + ChunkPos(0, 0, 1))) {
    westChunk = worldIn_->getChunk(position_ + ChunkPos(0, 0, 1));
  }
  const Chunk* eastChunk = nullptr;
  if(worldIn_->hasChunk(position_ - ChunkPos(0, 0, 1))) {
    eastChunk = worldIn_->getChunk(position_ - ChunkPos(0, 0, 1));
  }

  const BlockPos blockPos = position_ * 16;
  Block* block;

  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        block = block_[i + j * 16 + k * 256];
        if(block == nullptr) {
          continue;
        }
        if(block->id == 0) {
          block->side = Side::None;
          continue;
        }
        block->side = Side::Null;

        if(j == 15) {
          if(upChunk)
            block->side |= upChunk->getBlock(BlockPos(i, 0, k))->id == 0 ? Side::Up : Side::Null;
        }
        else
          block->side |= getBlock(BlockPos(i, j + 1, k))->id == 0 ? Side::Up : Side::Null;

        if(j == 0) {
          if(downChunk)
            block->side |= downChunk->getBlock(BlockPos(i, 15, k))->id == 0 ? Side::Down : Side::Null;
        }
        else
          block->side |= getBlock(BlockPos(i, j - 1, k))->id == 0 ? Side::Down : Side::Null;

        if(i == 0) {
          if(northChunk)
            block->side |= northChunk->getBlock(BlockPos(15, j, k))->id == 0 ? Side::North : Side::Null;
        }
        else
          block->side |= getBlock(BlockPos(i - 1, j, k))->id == 0 ? Side::North : Side::Null;

        if(i == 15) {
          if(southChunk)
            block->side |= southChunk->getBlock(BlockPos(0, j, k))->id == 0 ? Side::South : Side::Null;
        }
        else
          block->side |= getBlock(BlockPos(i + 1, j, k))->id == 0 ? Side::South : Side::Null;

        if(k == 15) {
          if(westChunk)
            block->side |= westChunk->getBlock(BlockPos(i, j, 0))->id == 0 ? Side::West : Side::Null;
        }
        else
          block->side |= getBlock(BlockPos(i, j, k + 1))->id == 0 ? Side::West : Side::Null;

        if(k == 0) {
          if(eastChunk)
            block->side |= eastChunk->getBlock(BlockPos(i, j, 15))->id == 0 ? Side::East : Side::Null;
        }
        else
          block->side |= getBlock(BlockPos(i, j, k - 1))->id == 0 ? Side::East : Side::Null;

        if(block->side == Side::Full)
          block->side = Side::All;
        else if(block->side == Side::Null)
          block->side = Side::None;
      }
    }
  }
  renderer_.computeBuffer(block_);
}

void Chunk::draw() const {
  /*glColor3ub(255, 255, 255);
  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        const Block& block = block_[i][j][k];
        if(to_underlying(block.side & Side::None)) {
          continue;
        }
        glBindTexture(GL_TEXTURE_2D, block.blockId);
  glPushMatrix();

  glTranslatef(i + static_cast<GLfloat>(position_.x) * 16, j + static_cast<GLfloat>(position_.y) * 16, k + static_cast<GLfloat>(position_.z) * 16);

  glBegin(GL_QUADS);

  if(to_underlying(block.side & Side::All)) {
    //Up side
    glTexCoord2s(0, 0);
    glVertex3s(0, 1, 1);
    glTexCoord2s(0, 1);
    glVertex3s(1, 1, 1);
    glTexCoord2s(1, 1);
    glVertex3s(1, 1, 0);
    glTexCoord2s(1, 0);
    glVertex3s(0, 1, 0);

    //Down side
    glTexCoord2s(0, 0);
    glVertex3s(1, 0, 1);
    glTexCoord2s(0, 1);
    glVertex3s(0, 0, 1);
    glTexCoord2s(1, 1);
    glVertex3s(0, 0, 0);
    glTexCoord2s(1, 0);
    glVertex3s(1, 0, 0);

    //North side
    glTexCoord2s(0, 0);
    glVertex3s(0, 1, 0);
    glTexCoord2s(0, 1);
    glVertex3s(0, 0, 0);
    glTexCoord2s(1, 1);
    glVertex3s(0, 0, 1);
    glTexCoord2s(1, 0);
    glVertex3s(0, 1, 1);

    //South side
    glTexCoord2s(0, 0);
    glVertex3s(1, 1, 1);
    glTexCoord2s(0, 1);
    glVertex3s(1, 0, 1);
    glTexCoord2s(1, 1);
    glVertex3s(1, 0, 0);
    glTexCoord2s(1, 0);
    glVertex3s(1, 1, 0);

    //West side
    glTexCoord2s(0, 0);
    glVertex3s(0, 1, 1);
    glTexCoord2s(0, 1);
    glVertex3s(0, 0, 1);
    glTexCoord2s(1, 1);
    glVertex3s(1, 0, 1);
    glTexCoord2s(1, 0);
    glVertex3s(1, 1, 1);

    //East side
    glTexCoord2s(0, 0);
    glVertex3s(1, 1, 0);
    glTexCoord2s(0, 1);
    glVertex3s(1, 0, 0);
    glTexCoord2s(1, 1);
    glVertex3s(0, 0, 0);
    glTexCoord2s(1, 0);
    glVertex3s(0, 1, 0);
  }
  else {
    if(to_underlying(block.side & Side::Up)) {
      //Up side
      glTexCoord2s(0, 0);
      glVertex3s(0, 1, 1);
      glTexCoord2s(0, 1);
      glVertex3s(1, 1, 1);
      glTexCoord2s(1, 1);
      glVertex3s(1, 1, 0);
      glTexCoord2s(1, 0);
      glVertex3s(0, 1, 0);
    }
    if(to_underlying(block.side & Side::Down)) {
      //Down side
      glTexCoord2s(0, 0);
      glVertex3s(1, 0, 1);
      glTexCoord2s(0, 1);
      glVertex3s(0, 0, 1);
      glTexCoord2s(1, 1);
      glVertex3s(0, 0, 0);
      glTexCoord2s(1, 0);
      glVertex3s(1, 0, 0);
    }
    if(to_underlying(block.side & Side::North)) {
      //North side
      glTexCoord2s(0, 0);
      glVertex3s(0, 1, 0);
      glTexCoord2s(0, 1);
      glVertex3s(0, 0, 0);
      glTexCoord2s(1, 1);
      glVertex3s(0, 0, 1);
      glTexCoord2s(1, 0);
      glVertex3s(0, 1, 1);
    }
    if(to_underlying(block.side & Side::South)) {
      //South side
      glTexCoord2s(0, 0);
      glVertex3s(1, 1, 1);
      glTexCoord2s(0, 1);
      glVertex3s(1, 0, 1);
      glTexCoord2s(1, 1);
      glVertex3s(1, 0, 0);
      glTexCoord2s(1, 0);
      glVertex3s(1, 1, 0);
    }
    if(to_underlying(block.side & Side::West)) {
      //West side
      glTexCoord2s(0, 0);
      glVertex3s(0, 1, 1);
      glTexCoord2s(0, 1);
      glVertex3s(0, 0, 1);
      glTexCoord2s(1, 1);
      glVertex3s(1, 0, 1);
      glTexCoord2s(1, 0);
      glVertex3s(1, 1, 1);
    }
    if(to_underlying(block.side & Side::East)) {
      //East side
      glTexCoord2s(0, 0);
      glVertex3s(1, 1, 0);
      glTexCoord2s(0, 1);
      glVertex3s(1, 0, 0);
      glTexCoord2s(1, 1);
      glVertex3s(0, 0, 0);
      glTexCoord2s(1, 0);
      glVertex3s(0, 1, 0);
    }
  }
  glEnd();

  glPopMatrix();
}
}
}*/

  glPushMatrix();
  glTranslated(static_cast<GLdouble>(position_.x * 16),
               static_cast<GLdouble>(position_.y * 16),
               static_cast<GLdouble>(position_.z * 16));
  renderer_.draw();
  glPopMatrix();

#ifdef DEBUG
  aabb_.drawAxisf(0.25F);
#endif // DEBUG
}