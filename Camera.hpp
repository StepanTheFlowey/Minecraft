#pragma once

#include "main.hpp"
#include "Vec3.hpp"
#include "Vec2.hpp"

#include <gl/GLU.h>

//Class for player camera
class Camera {
public:

  //
  Camera() = default;

  //
  ~Camera() = default;

  //
  void doTranlate() const;

  //
  void setPosition(const Vec3d& position);

  //
  void setRotation(const Vec2f& rotation);

  //
  void move(const Vec3d& offset);

  //
  void rotate(const Vec2f& rotation);

  //
  const Vec3d& getEyePosition() const;

  //
  const Vec3d& getCenterPosition() const;

  //
  const Vec2f& getRotation() const;
protected:

  void update();

  Vec3d eyePos_;    //Pos from
  Vec3d centerPos_; //Pos to
  Vec2f rotation_;
};

#include "Camera.inl"
