#pragma once

#include "vec3.hpp"
#include "side.hpp"

template <typename T> struct RayTraceResult {
  bool hit = false;
  enum class HitType : bool {
    Block,
    Entity
  };
  Side side;
  Vec3<T> pos;
  HitType hitType;
};

using RayTraceResultd = RayTraceResult<GLdouble>;
using RayTraceResultf = RayTraceResult<GLfloat>;