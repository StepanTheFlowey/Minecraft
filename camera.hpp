#pragma once
#include "types.hpp"

#include <gl/GLU.h>

class Camera {
  Vec3f eyePos_;
  Vec3f centerPos_;
  Vec2f rotation_;
public:
  Camera() {
#ifdef DEBUG
    std::wcout << L"Camera(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~Camera() {
#ifdef DEBUG
    std::wcout << L"~Camera(): Destructor" << std::endl;
#endif // DEBUG
  }

  void doTranlate() const {
    gluLookAt(eyePos_.x, eyePos_.y, eyePos_.z, centerPos_.x, centerPos_.y, centerPos_.z, 0.0, 1.0, 0.0);
  }

  void setPosition(Vec3f position) {
    eyePos_ = position;
    process();
  }

  void setRotation(Vec2f rotation) {
    rotation_ = rotation;
    process();
  }

  void move(Vec3f offset) {
    eyePos_ += offset;
    process();
  }

  void rotate(Vec2f rotation) {
    rotation_ += rotation;
    process();
  }

  constexpr Vec2f &getRotation() {
    return rotation_;
  }

  constexpr Vec3f &getEyePosition() {
    return eyePos_;
  }

  constexpr Vec3f &getCenterPosition() {
    return centerPos_;
  }
private:
  void process() {
    if(rotation_.x > 360.0F) {
      rotation_.x = 0.0F;
    }
    if(rotation_.x < 0.0F) {
      rotation_.x = 360.0F;
    }
    if(rotation_.y > 89.99F) {
      rotation_.y = 89.99F;
    }
    if(rotation_.y < -89.99F) {
      rotation_.y = -89.99F;
    }
    centerPos_.x = eyePos_.x + sinf(rotation_.x * DEG_TO_RAD_F) * cosf(rotation_.y * DEG_TO_RAD_F) * 5.0F;
    centerPos_.y = eyePos_.y + sinf(rotation_.y * DEG_TO_RAD_F) * 5.0F;
    centerPos_.z = eyePos_.z + cosf(rotation_.x * DEG_TO_RAD_F) * cosf(rotation_.y * DEG_TO_RAD_F) * 5.0F;
  }
};