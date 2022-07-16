#include "Camera.hpp"

#include "Math.hpp"

void Camera::doTranlate() const {
  gluLookAt(eyePos_.x, eyePos_.y, eyePos_.z, centerPos_.x, centerPos_.y, centerPos_.z, 0.0, 1.0, 0.0);
}

void Camera::setPosition(const Vec3d& position) {
  eyePos_ = position;
  update();
}

void Camera::setRotation(const Vec2f& rotation) {
  rotation_ = rotation;
  update();
}

void Camera::move(const Vec3d& offset) {
  eyePos_ += offset;
  update();
}

void Camera::rotate(const Vec2f& rotation) {
  rotation_ += rotation;
  update();
}

const Vec3d& Camera::getEyePosition() const {
  return eyePos_;
}

const Vec3d& Camera::getCenterPosition() const {
  return centerPos_;
}

const Vec2f& Camera::getRotation() const {
  return rotation_;
}

void Camera::update() {
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
