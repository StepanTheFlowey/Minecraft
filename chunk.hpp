#pragma once
#include "types.hpp"
#include "block.hpp"
#include "math.hpp"
#include "vbo.hpp"
#include "displayList.hpp"

#include <array>

//SFML
#include <SFML/Graphics.hpp>

class World;

class Chunk {
#ifdef DEBUG
  std::array<std::array<std::array<BlockRenderInfo, 16>, 16>, 16> block_;
#else
  BlockRenderInfo block_[16][16][16];
#endif // DEBUG
  std::weak_ptr<World> worldIn_;
  ChunkAabb aabb_;
  ChunkPos position_;
public:

  Chunk() {
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

  ~Chunk() {
#ifdef DEBUG
    std::wcout << L"~Chunk(): Destructor" << std::endl;
#endif // DEBUG
  }

  BlockRenderInfo &getBlockNative(SmallPos position) {
    return block_[position.x][position.y][position.z];
  }

  BlockRenderInfo &getBlockWorld(BlockPos position) {
    return getBlockNative(math::getBlockPosInChunk(position));
  }

  void setBlockNative(BlockPos position, BlockRenderInfo block) {
    block_[position.x][position.y][position.z] = block;
  }

  void setBlockWorld(BlockPos position, BlockRenderInfo block) {
    setBlockNative(math::getBlockPosInChunk(position), block);
  }

  void setPosition(ChunkPos position) {
    position_ = position;
    aabb_.minX = position_.x;
    aabb_.minY = position_.y;
    aabb_.minZ = position_.z;
    aabb_.maxX = position_.x + 16;
    aabb_.maxY = position_.y + 16;
    aabb_.maxZ = position_.z + 16;
  }

  ChunkPos &getPosition() {
    return position_;
  }

  ChunkAabb &getAabb() {
    return aabb_;
  }

  void setWorldIn(std::weak_ptr<World> worldIn) {
    worldIn_ = worldIn;
  }

  void computeBlocksEdgeRender();

  //auto &getData() {
  //  return block_;
  //}

  void draw() const {
    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          const BlockRenderInfo &block = block_[i][j][k];
          if(bitRead(block.sideRender, 1)) {
            continue;
          }
          glBindTexture(GL_TEXTURE_2D, block.blockId);
          glPushMatrix();

          glTranslatef(i + static_cast<GLfloat>(position_.x) * 16, j + static_cast<GLfloat>(position_.y) * 16, k + static_cast<GLfloat>(position_.z) * 16);

          glBegin(GL_QUADS);

          if(bitRead(block.sideRender, 0)) {
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
  private:
    std::shared_ptr<World> getWorldPtr() {
#ifdef DEBUG
      if(worldIn_.expired()) {
        throw std::out_of_range("worldIn_ is empty for chunk!");
      }
#endif // DEBUG
      return worldIn_.lock();
    }
};