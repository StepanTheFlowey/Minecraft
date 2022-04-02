#pragma once

#include "types.hpp"
#include "vec3.hpp"
#include "vec2.hpp"

#include <gl/GLU.h>

class Camera {
  Vec3d eyePos_;
  Vec3d centerPos_;
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

  inline void doTranlate() const {
    gluLookAt(eyePos_.x, eyePos_.y, eyePos_.z, centerPos_.x, centerPos_.y, centerPos_.z, 0.0, 1.0, 0.0);
  }

  void setPosition(Vec3d position) {
    eyePos_ = position;
    process();
  }

  void setRotation(Vec2f rotation) {
    rotation_ = rotation;
    process();
  }

  void move(Vec3d offset) {
    eyePos_ += offset;
    process();
  }

  void rotate(Vec2f rotation) {
    rotation_ += rotation;
    process();
  }

  inline const Vec3d &getEyePosition() const {
    return eyePos_;
  }

  inline const Vec3d &getCenterPosition() const {
    return centerPos_;
  }

  inline const Vec2f &getRotation() const {
    return rotation_;
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
    centerPos_.x = eyePos_.x + static_cast<double_t>(sinf(rotation_.x * F_DEG_TO_RAD) * cosf(rotation_.y * F_DEG_TO_RAD) * 5.0F);
    centerPos_.y = eyePos_.y + static_cast<double_t>(sinf(rotation_.y * F_DEG_TO_RAD) * 5.0F);
    centerPos_.z = eyePos_.z + static_cast<double_t>(cosf(rotation_.x * F_DEG_TO_RAD) * cosf(rotation_.y * F_DEG_TO_RAD) * 5.0F);
  }
};