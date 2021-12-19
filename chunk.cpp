#pragma once

#include "math.hpp"

Chunk::Chunk() {
#ifdef DEBUG
  std::wcout << L"Chunk(): Constructor" << std::endl;
#endif // DEBUG
  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        block_[i][j][k].blockId = rand() % 25 < 2 ? rand() % 15 : 0;
      }
    }
  }
}

Chunk::~Chunk() {
#ifdef DEBUG
  std::wcout << L"~Chunk(): Destructor" << std::endl;
#endif // DEBUG
}

BlockRenderInfo& Chunk::getBlockNative(SmallPos position) {
  return block_[position.x][position.y][position.z];
}

BlockRenderInfo& Chunk::getBlockWorld(BlockPos position) {
  return getBlockNative(math::getBlockPosInChunk(position));
}

void Chunk::setBlockNative(BlockPos position, BlockRenderInfo block) {
  block_[position.x][position.y][position.z] = block;
}

void Chunk::setBlockWorld(BlockPos position, BlockRenderInfo block) {
  setBlockNative(math::getBlockPosInChunk(position), block);
}

void Chunk::setPosition(ChunkPos position) {
  position_ = position;
  aabb_.min.x = position_.x;
  aabb_.min.y = position_.y;
  aabb_.min.z = position_.z;
  aabb_.max.x = position_.x + 16;
  aabb_.max.y = position_.y + 16;
  aabb_.max.z = position_.z + 16;
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

  BlockPos blockPos = position_ * 16;

  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        BlockRenderInfo& block = getBlockNative(BlockPos(i, j, k));
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

void Chunk::draw() const {
  for(uint8_t i = 0; i < 16; i++) {
    for(uint8_t j = 0; j < 16; j++) {
      for(uint8_t k = 0; k < 16; k++) {
        const BlockRenderInfo& block = block_[i][j][k];
        if(to_underlying<bool, Side>(block.side & Side::None)) {
          continue;
        }
        glBindTexture(GL_TEXTURE_2D, block.blockId);
        glPushMatrix();

        glTranslatef(i + static_cast<GLfloat>(position_.x) * 16, j + static_cast<GLfloat>(position_.y) * 16, k + static_cast<GLfloat>(position_.z) * 16);

        glBegin(GL_QUADS);

        if(to_underlying<bool, Side>(block.side & Side::All)) {
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
          if(bitRead(block.sideRender, 2)) {
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
          if(bitRead(block.sideRender, 3)) {
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
          if(bitRead(block.sideRender, 4)) {
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
          if(bitRead(block.sideRender, 5)) {
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
          if(bitRead(block.sideRender, 6)) {
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
          if(bitRead(block.sideRender, 7)) {
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
  }
  aabb_.drawAxisf();
}

std::shared_ptr<World> Chunk::getWorldPtr() {
#ifdef DEBUG
  if(worldIn_.expired()) {
    throw std::out_of_range("worldIn_ is empty for chunk!");
  }
#endif // DEBUG
  return worldIn_.lock();
}