#include "chunk.hpp"

#include "world.hpp"

Chunk::Chunk() {
#ifdef DEBUG
  std::wcout << L"Chunk()" << std::endl;
#endif // DEBUG
  for(uint16_t i = 0; i < 4096; i++) {
    block_[i].blockId = rand() % 25 < 2 ? rand() % 15 : 0;
  }
}

Chunk::~Chunk() {
#ifdef DEBUG
  std::wcout << L"~Chunk()" << std::endl;
#endif // DEBUG
}

BlockRenderInfo& Chunk::getBlockNative(SmallPos position) {
  return block_[position.x + position.y * 16 + position.z * 256];
}

BlockRenderInfo& Chunk::getBlockWorld(BlockPos position) {
  return getBlockNative(getBlockPosInChunk(position));
}

void Chunk::setBlockNative(BlockPos position, BlockRenderInfo block) {
  block_[position.x + position.y * 16 + position.z * 256] = block;
}

void Chunk::setBlockWorld(BlockPos position, BlockRenderInfo block) {
  setBlockNative(getBlockPosInChunk(position), block);
}

void Chunk::setPosition(ChunkPos position) {
  position_ = position;
  aabb_.min = position_ * 16;
  aabb_.max = position_ * 16 + 16;
}

ChunkPos& Chunk::getPosition() {
  return position_;
}

ChunkAabb& Chunk::getAabb() {
  return aabb_;
}

void Chunk::setWorldIn(std::weak_ptr<World> worldIn) {
  worldIn_ = worldIn;
}

//HACK: sides
void Chunk::computeBlocksEdgeRender() {
  std::shared_ptr<World> world = getWorldPtr();

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

  const BlockPos blockPos = position_ * 16;

  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        BlockRenderInfo& block = getBlockNative(BlockPos(i, j, k));
        if(block.blockId == 0) {
          block.side = Side::None;
          continue;
        }
        block.side = Side::Null;

        if(j == 15) {
          if(upChunk)
            block.side |= upChunk->getBlockNative(BlockPos(i, 0, k)).blockId == 0 ? Side::Up : Side::Null;
        }
        else
          block.side |= getBlockNative(BlockPos(i, j + 1, k)).blockId == 0 ? Side::Up : Side::Null;

        if(j == 0) {
          if(downChunk)
            block.side |= downChunk->getBlockNative(BlockPos(i, 15, k)).blockId == 0 ? Side::Down : Side::Null;
        }
        else
          block.side |= getBlockNative(BlockPos(i, j - 1, k)).blockId == 0 ? Side::Down : Side::Null;

        if(i == 0) {
          if(northChunk)
            block.side |= northChunk->getBlockNative(BlockPos(15, j, k)).blockId == 0 ? Side::North : Side::Null;
        }
        else
          block.side |= getBlockNative(BlockPos(i - 1, j, k)).blockId == 0 ? Side::North : Side::Null;

        if(i == 15) {
          if(southChunk)
            block.side |= southChunk->getBlockNative(BlockPos(0, j, k)).blockId == 0 ? Side::South : Side::Null;
        }
        else
          block.side |= getBlockNative(BlockPos(i + 1, j, k)).blockId == 0 ? Side::South : Side::Null;

        if(k == 15) {
          if(westChunk)
            block.side |= westChunk->getBlockNative(BlockPos(i, j, 0)).blockId == 0 ? Side::West : Side::Null;
        }
        else
          block.side |= getBlockNative(BlockPos(i, j, k + 1)).blockId == 0 ? Side::West : Side::Null;

        if(k == 0) {
          if(eastChunk)
            block.side |= eastChunk->getBlockNative(BlockPos(i, j, 15)).blockId == 0 ? Side::East : Side::Null;
        }
        else
          block.side |= getBlockNative(BlockPos(i, j, k - 1)).blockId == 0 ? Side::East : Side::Null;

        if(block.side == Side::Full) {
          block.side = Side::All;
        }
        else if(block.side == Side::Null) {
          block.side = Side::None;
        }
      }
    }
  }
  renderer.computeBuffer(block_);
}

void Chunk::draw() const {
  /*glColor3ub(255, 255, 255);
  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        const BlockRenderInfo& block = block_[i][j][k];
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
  glTranslatef(position_.x * 16, position_.y * 16, position_.z * 16);
  renderer.draw();
  glPopMatrix();
#ifdef DEBUG
  aabb_.drawAxisf(0.25F);
#endif // DEBUG
}

std::shared_ptr<World> Chunk::getWorldPtr() {
#ifdef DEBUG
  if(worldIn_.expired()) {
    throw std::out_of_range("worldIn_ is empty for chunk!");
  }
#endif // DEBUG
  return worldIn_.lock();
}