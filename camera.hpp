#pragma once

#include "main.hpp"
#include "Vec3.hpp"
#include "Vec2.hpp"

#include <gl/GLU.h>

class Camera {
  Vec3d eyePos_;
  Vec3d centerPos_;
  Vec2f rotation_;
public:

  inline Camera() {
    debug(L"Camera()");
  }

  inline ~Camera() {
    debug(L"~Camera()");
  }

  inline void doTranlate() const {
    gluLookAt(eyePos_.x, eyePos_.y, eyePos_.z, centerPos_.x, centerPos_.y, centerPos_.z, 0.0, 1.0, 0.0);
  }

  inline void setPosition(const Vec3d position) {
    eyePos_ = position;
    process();
  }

  inline void setRotation(const Vec2f rotation) {
    rotation_ = rotation;
    process();
  }

  inline void move(const Vec3d offset) {
    eyePos_ += offset;
    process();
  }

  inline void rotate(const Vec2f rotation) {
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

  void process();
};
