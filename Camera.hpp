#pragma once

#include "main.hpp"
#include "Vec3.hpp"
#include "Vec2.hpp"

#include <gl/GLU.h>

//Class for player camera
class Camera {
  Vec3d eyePos_;    //Pos from
  Vec3d centerPos_; //Pos to
  Vec2f rotation_;
public:

  inline Camera();

  inline ~Camera();

  inline void doTranlate() const;

  inline void setPosition(const Vec3d position);

  inline void setRotation(const Vec2f rotation);

  inline void move(const Vec3d offset);

  inline void rotate(const Vec2f rotation);

  inline const Vec3d& getEyePosition() const;

  inline const Vec3d& getCenterPosition() const;

  inline const Vec2f& getRotation() const;
private:

  void process();
};

#include "Camera.inl"
