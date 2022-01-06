#include "player.hpp"

#include "math.hpp"
#include "color.hpp"
#include "collisionResult.hpp"
#include "chunk.hpp"

Player::Player():position_(1, 20, 1) {
#ifdef DEBUG
  std::wcout << L"Player()" << std::endl;
#endif // DEBUG
  camera.setPosition(position_);
}

Player::~Player() {
#ifdef DEBUG
  std::wcout << L"~Player()" << std::endl;
#endif // DEBUG
  worldIn_.reset();
}

void Player::setMoveDirection(Side direction, bool enable = true) {
  if(enable) {
    moveDir_ |= direction;
  }
  else {
    moveDir_ ^= direction;
  }
}

void Player::breakBlock() {
  if(isBlockMouseOver_) {
    worldIn_->setBlock(blockMouseOver_.pos, BlockRenderInfo());
    worldIn_->getChunk(getChunkPosFromBlock(blockMouseOver_.pos))->computeBlocksEdgeRender();
  }
}

void Player::placeBlock() {
  if(isBlockMouseOver_) {
    BlockPos pos = blockMouseOver_.pos;
    switch(blockMouseOver_.side) {
      case Side::Up:
        pos.y++;
        break;
      case Side::Down:
        pos.y--;
        break;
      case Side::North:
        pos.x--;
        break;
      case Side::South:
        pos.x++;
        break;
      case Side::West:
        pos.z++;
        break;
      case Side::East:
        pos.z--;
        break;
    }
    worldIn_->setBlock(pos, BlockRenderInfo {static_cast<uint16_t>(rand() % 15 + 1)});
    if(blockMouseOver_.pos != pos) {
      worldIn_->getChunk(getChunkPosFromBlock(blockMouseOver_.pos))->computeBlocksEdgeRender();
    }
    worldIn_->getChunk(getChunkPosFromBlock(pos))->computeBlocksEdgeRender();
  }
}

void Player::setWorldIn(std::shared_ptr<World> worldIn) {
  worldIn_ = worldIn;
}

void Player::move(Vec3d offset) {
  position_ += offset;
  camera.setPosition(position_);
}

void Player::update(Time time) {
  const Vec2f& rotation = camera.getRotation();
  const float_t millis = static_cast<float_t>(time.asMilliseconds());
  if(to_underlying(moveDir_ & Side::Forward)) {
    move(
      Vec3d(
      static_cast<double_t>(sinf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * millis),
      0.0,
      static_cast<double_t>(cosf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Back)) {
    move(
      Vec3d(
      static_cast<double_t>(sinf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * -millis),
      0.0,
      static_cast<double_t>(cosf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * -millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Left)) {
    move(
      Vec3d(
      static_cast<double_t>(cosf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * millis),
      0.0,
      static_cast<double_t>(sinf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * -millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Right)) {
    move(
      Vec3d(
      static_cast<double_t>(cosf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * -millis),
      0.0,
      static_cast<double_t>(sinf(rotation.x * DEG_TO_RAD_F) * moveSpeed_ * millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Up)) {
    move(Vec3d(0, moveSpeed_ * millis, 0));
  }
  if(to_underlying(moveDir_ & Side::Down)) {
    move(Vec3d(0, moveSpeed_ * -millis, 0));
  }

  colorDeg += static_cast<float_t>(millis) / 10;
  if(colorDeg > 360) {
    colorDeg = 0;
  }
  //TODO: how about realestic walk?
  const Vec3f& eyePos = camera.getEyePosition();
  const Vec3f& viewPos = camera.getCenterPosition();
  const Aabb3d lineBox(eyePos, viewPos);

  bool allSides = false;
  CollisionResultd collisionResult;
  BlockRenderInfo block;
  Rect3d rect;
  Vec3d pos;
  std::vector<BlockWithSide> mathed;
  mathed.reserve(10);

  for(auto& [iKey, iVal] : worldIn_->region_) {
    for(auto& [jKey, jVal] : iVal) {
      if(jVal->getAabb().intersects(lineBox)) {
        for(auto& [kKey, kVal] : jVal->chunk_) {
          for(auto& [lKey, lVal] : kVal) {
            for(auto& [mKey, mVal] : lVal) {
              if(mVal->getAabb().intersects(lineBox)) {
                for(uint8_t i = 0; i < 16; i++) {
                  for(uint8_t j = 0; j < 16; j++) {
                    for(uint8_t k = 0; k < 16; k++) {
                      block = mVal->getBlockNative(BlockPos(i, j, k));
                      if(block.blockId == 0 || block.side == Side::None) {
                        continue;
                      }

                      allSides = block.side == Side::All;
                      pos = mVal->getPosition() * 16 + Vec3f(i, j, k);

                      if(to_underlying(block.side & Side::Up) || allSides) {
                        //Up side collision check
                        rect = Rect3d::Up + pos;
                        collisionResult = math::rectLineCollision<GLdouble>(rect, Vec3d(0, 1, 0), eyePos, viewPos);
                        if(collisionResult.hit) {
                          mathed.push_back({pos, Side::Up});
                          continue;
                        }
                      }

                      if(to_underlying(block.side & Side::Down) || allSides) {
                        //Down side collision check
                        rect = Rect3d::Down + pos;
                        collisionResult = math::rectLineCollision<GLdouble>(rect, Vec3d(0, -1, 0), eyePos, viewPos);
                        if(collisionResult.hit) {
                          mathed.push_back({pos, Side::Down});
                          continue;
                        }
                      }

                      if(to_underlying(block.side & Side::North) || allSides) {
                        //North side collision check
                        rect = Rect3d::North + pos;
                        collisionResult = math::rectLineCollision<GLdouble>(rect, Vec3d(-1, 0, 0), eyePos, viewPos);
                        if(collisionResult.hit) {
                          mathed.push_back({pos, Side::North});
                          continue;
                        }
                      }

                      if(to_underlying(block.side & Side::South) || allSides) {
                        //South side collision check
                        rect = Rect3d::South + pos;
                        collisionResult = math::rectLineCollision<GLdouble>(rect, Vec3d(1, 0, 0), eyePos, viewPos);
                        if(collisionResult.hit) {
                          mathed.push_back({pos, Side::South});
                          continue;
                        }
                      }

                      if(to_underlying(block.side & Side::West) || allSides) {
                        //West side collision check
                        rect = Rect3d::West + pos;
                        collisionResult = math::rectLineCollision<GLdouble>(rect, Vec3d(0, 0, 1), eyePos, viewPos);
                        if(collisionResult.hit) {
                          mathed.push_back({pos, Side::West});
                          continue;
                        }
                      }

                      if(to_underlying(block.side & Side::East) || allSides) {
                        //East side collision check
                        rect = Rect3d::East + pos;
                        collisionResult = math::rectLineCollision<GLdouble>(rect, Vec3d(0, 0, -1), eyePos, viewPos);
                        if(collisionResult.hit) {
                          mathed.push_back({pos, Side::East});
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

void Player::draw() {
  //TODO: Drawing player model

  Vec3f pos(blockMouseOver_.pos);
#ifdef DEBUG
  BlockAabb(pos, pos + Vec3f(1, 1, 1)).drawAxisColorf(Color(0, 255, 0), 0.0001F);

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
  BlockAabb(pos, pos + Vec3f(1, 1, 1)).drawAxisColorf(Color(0, 0, 0), 0.0001F);
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