#include "Camera.hpp"

#include "Math.hpp"

void Camera::process() {
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
