#include "Player.hpp"

#include "main.hpp"
#include "World.hpp"
#include "Chunk.hpp"
#include "Block.hpp"
#include "Math.hpp"
#include "CollisionResult.hpp"
#include "Color.hpp"
#include "Side.hpp"

void Player::walk(const Side direction, const bool enable) {
  if(enable) {
    moveDir_ |= direction;
  }
  else {
    moveDir_ ^= direction;
  }
}

void Player::placeBlock() {
  if(isBlockMouseOver_) {
    BlockPos pos = blockMouseOver_.pos;
    switch(blockMouseOver_.side) {
      case Side::Up:
        ++pos.y;
        break;
      case Side::Down:
        --pos.y;
        break;
      case Side::North:
        --pos.x;
        break;
      case Side::South:
        ++pos.x;
        break;
      case Side::West:
        ++pos.z;
        break;
      case Side::East:
        --pos.z;
        break;
    }
    world->setBlock(pos, new Block{static_cast<Side>(rand() % 15 + 1)});
    if(blockMouseOver_.pos != pos) {
      world->getChunk(getChunkPosFromBlock(blockMouseOver_.pos))->computeBlocksEdgeRender();
    }
    world->getChunk(getChunkPosFromBlock(pos))->computeBlocksEdgeRender();
  }
}

void Player::breakBlock() {
  if(isBlockMouseOver_) {
    world->setBlock(blockMouseOver_.pos, createBlock<Block>());
    world->getChunk(getChunkPosFromBlock(blockMouseOver_.pos))->computeBlocksEdgeRender();
  }
}

void Player::move(const Vec3d offset) {
  position_ += offset;
  camera.setPosition(position_);
}

void Player::update(const Time time) {
  const Vec2f& rotation = camera.getRotation();
  const float_t millis = static_cast<float_t>(time.asMilliseconds());
  if(to_underlying(moveDir_ & Side::Forward)) {
    move(
      Vec3d(
      static_cast<double_t>(sinf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * millis),
      0.0,
      static_cast<double_t>(cosf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Back)) {// если (to_underlying(moveDir_ & Side::Back))
    move(
      Vec3d(
      static_cast<double_t>(sinf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * -millis),
      0.0,
      static_cast<double_t>(cosf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * -millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Left)) {
    move(
      Vec3d(
      static_cast<double_t>(cosf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * millis),
      0.0,
      static_cast<double_t>(sinf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * -millis))
    );
  }
  if(to_underlying(moveDir_ & Side::Right)) {
    move(
      Vec3d(
      static_cast<double_t>(cosf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * -millis),
      0.0,
      static_cast<double_t>(sinf(rotation.x * F_DEG_TO_RAD) * moveSpeed_ * millis))
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
  const Vec3d& eyePos = camera.getEyePosition();
  const Vec3d& viewPos = camera.getCenterPosition();
  const Aabb3d lineBox(eyePos, viewPos);

  bool allSides = false;
  CollisionResultd collisionResult;
  const Block* block = nullptr;
  Rect3d rect;
  SmallPos blockPosInChunk;
  Vec3d pos;
  std::vector<BlockWithSide> mathed;
  mathed.reserve(10);

  for(auto& [iKey, iVal] : world->region_) {
    if(iVal == nullptr) continue;
    if(iVal->getAabb().intersects(lineBox)) {
      for(auto& j : iVal->chunk_) {
        if(j == nullptr) continue;
        if(j->getAabb().intersects(lineBox)) {
          for(uint16_t i = 0; i < 4096; ++i) {
            blockPosInChunk = getBlockPosFromIndex(i);
            block = j->getBlock(blockPosInChunk);
            if(block == nullptr) continue;
            if(block->id == 0 || block->side == Side::None) continue;

            allSides = block->side == Side::All;
            pos = j->getPosition() * 16 + blockPosInChunk;

            if(to_underlying(block->side & Side::Up) || allSides) {
              //Up side collision check
              collisionResult = math::rectLineCollision<GLdouble>(Rect3d::Up + pos, Vec3d(0, 1, 0), eyePos, viewPos);
              if(collisionResult.hit) {
                mathed.push_back({pos, Side::Up});
                continue;
              }
            }

            if(to_underlying(block->side & Side::Down) || allSides) {
              //Down side collision check
              collisionResult = math::rectLineCollision<GLdouble>(Rect3d::Down + pos, Vec3d(0, -1, 0), eyePos, viewPos);
              if(collisionResult.hit) {
                mathed.push_back({pos, Side::Down});
                continue;
              }
            }

            if(to_underlying(block->side & Side::North) || allSides) {
              //North side collision check
              collisionResult = math::rectLineCollision<GLdouble>(Rect3d::North + pos, Vec3d(-1, 0, 0), eyePos, viewPos);
              if(collisionResult.hit) {
                mathed.push_back({pos, Side::North});
                continue;
              }
            }

            if(to_underlying(block->side & Side::South) || allSides) {
              //South side collision check
              collisionResult = math::rectLineCollision<GLdouble>(Rect3d::South + pos, Vec3d(1, 0, 0), eyePos, viewPos);
              if(collisionResult.hit) {
                mathed.push_back({pos, Side::South});
                continue;
              }
            }

            if(to_underlying(block->side & Side::West) || allSides) {
              //West side collision check
              collisionResult = math::rectLineCollision<GLdouble>(Rect3d::West + pos, Vec3d(0, 0, 1), eyePos, viewPos);
              if(collisionResult.hit) {
                mathed.push_back({pos, Side::West});
                continue;
              }
            }

            if(to_underlying(block->side & Side::East) || allSides) {
              //East side collision check
              collisionResult = math::rectLineCollision<GLdouble>(Rect3d::East + pos, Vec3d(0, 0, -1), eyePos, viewPos);
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
exitTrace:
  int8_t smallerNum = -1;
  for(uint8_t i = 0; i < mathed.size(); ++i) {
    bool smaller = true;
    for(uint8_t j = 0; j < mathed.size(); ++j) {
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

void Player::draw() const {
  //TODO: Drawing player model

  Vec3f pos(blockMouseOver_.pos);

#ifdef DEBUG
  BlockAabb(pos, pos + Vec3f(1, 1, 1)).drawAxisColorf(Color(0, 255, 0), 0.0001F);

  glPushMatrix();


  glTranslated(pos.x, pos.y, pos.z);

  float_t sinValue = abs(sinf(colorDeg * (float_t)DEG_TO_RAD)) * 255;
  glColor3ub(0, 0, static_cast<GLubyte>(sinValue));

  glBegin(GL_QUADS);

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
  glVertex3f(pos.x + 3.5F, pos.y + 0.5F, pos.z + 0.5F);
  glVertex3f(pos.x - 2.5F, pos.y + 0.5F, pos.z + 0.5F);

  glColor3ub(0, 255, 0);
  glVertex3f(pos.x + 0.5F, pos.y + 3.5F, pos.z + 0.5F);
  glVertex3f(pos.x + 0.5F, pos.y - 2.5F, pos.z + 0.5F);

  glColor3ub(0, 0, 255);
  glVertex3f(pos.x + 0.5F, pos.y + 0.5F, pos.z + 3.5F);
  glVertex3f(pos.x + 0.5F, pos.y + 0.5F, pos.z - 2.5F);

  glEnd();
#endif // DEBUG
}
