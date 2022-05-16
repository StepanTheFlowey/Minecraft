#pragma once

inline Camera::Camera() {
  debug(L"Camera()");
}

inline Camera::~Camera() {
  debug(L"~Camera()");
}

inline void Camera::doTranlate() const {
  gluLookAt(eyePos_.x, eyePos_.y, eyePos_.z, centerPos_.x, centerPos_.y, centerPos_.z, 0.0, 1.0, 0.0);
}

inline void Camera::setPosition(const Vec3d position) {
  eyePos_ = position;
  process();
}

inline void Camera::setRotation(const Vec2f rotation) {
  rotation_ = rotation;
  process();
}

inline void Camera::move(const Vec3d offset) {
  eyePos_ += offset;
  process();
}

inline void Camera::rotate(const Vec2f rotation) {
  rotation_ += rotation;
  process();
}

inline const Vec3d& Camera::getEyePosition() const {
  return eyePos_;
}

inline const Vec3d& Camera::getCenterPosition() const {
  return centerPos_;
}

inline const Vec2f& Camera::getRotation() const {
  return rotation_;
}
