#pragma once
#include "types.hpp"
#include "world.hpp"
#include "camera.hpp"

class Player {
  uint8_t walkParam_ = 0;                 //Active walk dir 
  double_t walkSpeed_ = 0.005;            //Player walk speed
  Vec3d position_;

  std::shared_ptr<World> worldIn_ = nullptr;                //World in

  float_t colorDeg = 0;
  BlockWithSide blockMouseOver_;
  bool isBlockMouseOver_ = false;
public:
  Camera camera; //Camera object

  Player() {
#ifdef DEBUG
    std::wcout << L"Player(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~Player() {
#ifdef DEBUG
    std::wcout << L"~Player(): Destructor" << std::endl;
#endif // DEBUG
    worldIn_.reset();
  }

  //Disable or enable walking in specific direction
  //TODO: replace this by func(enum or uint8_t walkDir, bool val);
  void goForward(bool val) {
    bitWrite(walkParam_, 0, val);
  }
  void goBack(bool val) {
    bitWrite(walkParam_, 1, val);
  }
  void goLeft(bool val) {
    bitWrite(walkParam_, 2, val);
  }
  void goRight(bool val) {
    bitWrite(walkParam_, 3, val);
  }
  void goUp(bool val) {
    bitWrite(walkParam_, 4, val);
  }
  void goDown(bool val) {
    bitWrite(walkParam_, 5, val);
  }

  void breakBlock() {
    if(isBlockMouseOver_) {
      worldIn_->setBlock(blockMouseOver_.pos, BlockRenderInfo());
      worldIn_->getChunk(math::getChunkPosFromBlock(blockMouseOver_.pos))->computeBlocksEdgeRender();
    }
  }

  void placeBlock() {
    if(isBlockMouseOver_) {
      BlockPos pos = blockMouseOver_.pos;
      switch(blockMouseOver_.side) {
        case Side::Up:
          pos.y++;
          if(pos.y > 15) {
            return;
          }
          break;
        case Side::Down:
          pos.y--;
          if(pos.y < 0) {
            return;
          }
          break;
        case Side::North:
          pos.x--;
          if(pos.x < 0) {
            return;
          }
          break;
        case Side::South:
          pos.x++;
          if(pos.x > 15) {
            return;
          }
          break;
        case Side::West:
          pos.z++;
          if(pos.z > 15) {
            return;
          }
          break;
        case Side::East:
          pos.z--;
          if(pos.z < 0) {
            return;
          }
          break;
      }
      worldIn_->setBlock(pos, BlockRenderInfo {static_cast<uint16_t>(rand() % 15 + 1)});
      worldIn_->getChunk(math::getChunkPosFromBlock(blockMouseOver_.pos))->computeBlocksEdgeRender();
    }
  }

  void setWorldIn(std::shared_ptr<World> worldIn) {
    worldIn_ = worldIn;
  }

  void move(double_t x, double_t y, double_t z) {
    position_ += Vec3d(x, y, z);
    camera.setPosition(position_);
  }

  void update(gametime_t timeLeft) {
    //Move offset calculating: TimeAfterLastGameDisplay * WalkSpeed * other
    Vec2f &rotation = camera.getRotation();
    if(bitRead(walkParam_, 0)) {//Walk forward
      move(sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft, 0, cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft);
    }
    if(bitRead(walkParam_, 1)) {//Walk back
      move(sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft, 0, cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft);
    }
    if(bitRead(walkParam_, 2)) {//Walk left
      move(cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft, 0, sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft);
    }
    if(bitRead(walkParam_, 3)) {//Walk right
      move(cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft, 0, sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft);
    }
    if(bitRead(walkParam_, 4)) {//Walk up
      move(0, walkSpeed_ * timeLeft, 0);
    }
    if(bitRead(walkParam_, 5)) {//Walk down
      move(0, walkSpeed_ * -timeLeft, 0);
    }

    colorDeg += static_cast<float_t>(timeLeft) / 10;
    if(colorDeg > 360) {
      colorDeg = 0;
    }
    //TODO: how about realestic walk?
    const Vec3f eyePos = camera.getEyePosition();
    const Vec3f viewPos = camera.getCenterPosition();
    const Aabb<GLfloat> lineAABB(eyePos, viewPos);

    RayTraceResultf rayResult;
    BlockPlane plane;
    BlockRenderInfo block;
    std::vector<BlockWithSide> mathed;
    mathed.reserve(10);

    for(auto &[iKey, iVal] : worldIn_->getData()) {
      for(auto &[jKey, jVal] : iVal) {
        if(jVal->getAabb().intersects(lineAABB)) {
          for(auto &[kKey, kVal] : jVal->getData()) {
            for(auto &[lKey, lVal] : kVal) {
              for(auto &[mKey, mVal] : lVal) {
                if(mVal->getAabb().intersects(lineAABB)) {
                  for(uint8_t i = 0; i < 16; i++) {
                    for(uint8_t j = 0; j < 16; j++) {
                      for(uint8_t k = 0; k < 16; k++) {
                        block = mVal->getBlockNative(BlockPos(i, j, k));
                        if(block.blockId == 0) {
                          continue;
                        }

                        if(bitRead(block.sideRender, 2)) {
                          //Up side collision check
                          plane.A = SmallPos(i + 1, j + 1, k);
                          plane.C = SmallPos(i, j + 1, k);
                          plane.B = SmallPos(i, j + 1, k + 1);
                          rayResult = math::raytrace::planeLineCollision<GLfloat>(plane, eyePos, viewPos);
                          if(rayResult.hit) {
                            mathed.push_back({BlockPos(i, j, k), Side::Up});
                            continue;
                          }
                        }

                        if(bitRead(block.sideRender, 3)) {
                          //Down side collision check
                          plane.A = SmallPos(i + 1, j, k);
                          plane.B = SmallPos(i, j, k);
                          plane.C = SmallPos(i, j, k + 1);
                          rayResult = math::raytrace::planeLineCollision<GLfloat>(plane, eyePos, viewPos);
                          if(rayResult.hit) {
                            mathed.push_back({BlockPos(i, j, k), Side::Down});
                            continue;
                          }
                        }

                        if(bitRead(block.sideRender, 4)) {
                          //North side collision check
                          plane.A = SmallPos(i, j, k);
                          plane.B = SmallPos(i, j + 1, k);
                          plane.C = SmallPos(i, j, k + 1);
                          rayResult = math::raytrace::planeLineCollision<GLfloat>(plane, eyePos, viewPos);
                          if(rayResult.hit) {
                            mathed.push_back({BlockPos(i, j, k), Side::North});
                            continue;
                          }
                        }

                        if(bitRead(block.sideRender, 5)) {
                          //South side collision check
                          plane.A = SmallPos(i + 1, j, k);
                          plane.C = SmallPos(i + 1, j + 1, k);
                          plane.B = SmallPos(i + 1, j, k + 1);
                          rayResult = math::raytrace::planeLineCollision<GLfloat>(plane, eyePos, viewPos);
                          if(rayResult.hit) {
                            mathed.push_back({BlockPos(i, j, k), Side::South});
                            continue;
                          }
                        }

                        if(bitRead(block.sideRender, 6)) {
                          //West side collision check
                          plane.A = SmallPos(i + 1, j, k + 1);
                          plane.C = SmallPos(i, j + 1, k + 1);
                          plane.B = SmallPos(i, j, k + 1);
                          rayResult = math::raytrace::planeLineCollision<GLfloat>(plane, eyePos, viewPos);
                          if(rayResult.hit) {
                            mathed.push_back({BlockPos(i, j, k), Side::West});
                            continue;
                          }
                        }

                        if(bitRead(block.sideRender, 7)) {
                          //East side collision check
                          plane.A = SmallPos(i + 1, j, k);
                          plane.B = SmallPos(i, j + 1, k);
                          plane.C = SmallPos(i, j, k);
                          rayResult = math::raytrace::planeLineCollision<GLfloat>(plane, eyePos, viewPos);
                          if(rayResult.hit) {
                            mathed.push_back({BlockPos(i, j, k), Side::East});
                            continue;
                          }
                        }

                        if(mathed.size() == 10) {
                          goto exitTrace;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  exitTrace:
    int8_t smallerNum = -1;
    for(uint8_t i = 0; i < mathed.size(); i++) {
      bool smaller = true;
      for(uint8_t j = 0; j < mathed.size(); j++) {
        if(i == j) {
          continue;
        }
        smaller = smaller && mathed[i].pos.distanceTo(eyePos) < mathed[j].pos.distanceTo(eyePos);
      }
      if(smaller) {
        smallerNum = i;
      }
    }
    if(smallerNum == -1) {
      blockMouseOver_.pos = BlockPos(-1, -1, -1);
      blockMouseOver_.side = Side::None;
      isBlockMouseOver_ = false;
    }
    else {
      blockMouseOver_ = mathed[smallerNum];
      isBlockMouseOver_ = true;
    }
  }

  void draw() {
    //TODO: Drawing player model

    Vec3f pos(blockMouseOver_.pos);
#ifdef DEBUG
    BlockAabb(pos, pos + Vec3f(1, 1, 1)).drawColorf(Color(0, 255, 0));

    glPushMatrix();

    glTranslated(pos.x, pos.y, pos.z);

    glBegin(GL_QUADS);

    float_t sinValue = abs(sinf(colorDeg * (float_t) DEG_TO_RAD)) * 255;
    glColor3ub(0, 0, static_cast<GLubyte>(sinValue));

    if(blockMouseOver_.side == Side::Up) {
      //Up side
      glVertex3f(0.0F, 1.05F, 1.0F);
      glVertex3f(1.0F, 1.05F, 1.0F);
      glVertex3f(1.0F, 1.05F, 0.0F);
      glVertex3f(0.0F, 1.05F, 0.0F);
    }
    if(blockMouseOver_.side == Side::Down) {
      //Down side
      glVertex3f(1.0F, -0.05F, 1.0F);
      glVertex3f(0.0F, -0.05F, 1.0F);
      glVertex3f(0.0F, -0.05F, 0.0F);
      glVertex3f(1.0F, -0.05F, 0.0F);
    }
    if(blockMouseOver_.side == Side::North) {
      //North side
      glVertex3f(-0.05F, 1.0F, 0.0F);
      glVertex3f(-0.05F, 0.0F, 0.0F);
      glVertex3f(-0.05F, 0.0F, 1.0F);
      glVertex3f(-0.05F, 1.0F, 1.0F);
    }
    if(blockMouseOver_.side == Side::South) {
      //South side
      glVertex3f(1.05F, 1.0F, 1.0F);
      glVertex3f(1.05F, 0.0F, 1.0F);
      glVertex3f(1.05F, 0.0F, 0.0F);
      glVertex3f(1.05F, 1.0F, 0.0F);
    }
    if(blockMouseOver_.side == Side::West) {
      //West side
      glVertex3f(0.0F, 1.0F, 1.05F);
      glVertex3f(0.0F, 0.0F, 1.05F);
      glVertex3f(1.0F, 0.0F, 1.05F);
      glVertex3f(1.0F, 1.0F, 1.05F);
    }
    if(blockMouseOver_.side == Side::East) {
      //East side
      glVertex3f(1.0F, 1.0F, -0.05F);
      glVertex3f(1.0F, 0.0F, -0.05F);
      glVertex3f(0.0F, 0.0F, -0.05F);
      glVertex3f(0.0F, 1.0F, -0.05F);
    }

    glEnd();

    glPopMatrix();
#else //!DEBUG
    BlockAabb(pos, pos + Vec3f(1, 1, 1)).drawColorf(Color(0, 0, 0));
#endif // DEBUG
#ifdef DEBUG
    glBegin(GL_LINES);

    glColor3ub(255, 0, 0);
    glVertex3f(pos.x + 3, pos.y + 0.5F, pos.z + 0.5F);
    glVertex3f(pos.x - 2.5F, pos.y + 0.5F, pos.z + 0.5F);

    glColor3ub(0, 255, 0);
    glVertex3f(pos.x + 0.5F, pos.y + 3, pos.z + 0.5F);
    glVertex3f(pos.x + 0.5F, pos.y - 2.5F, pos.z + 0.5F);

    glColor3ub(0, 0, 255);
    glVertex3f(pos.x + 0.5F, pos.y + 0.5F, pos.z + 3);
    glVertex3f(pos.x + 0.5F, pos.y + 0.5F, pos.z - 2.5F);

    glEnd();
#endif // DEBUG
  }
};