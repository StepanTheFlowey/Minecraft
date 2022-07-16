#pragma once

#include "Vec3.hpp"

template <typename T>
class Plane3 {
public:

  Vec3<T> point;
  Vec3<T> normal;

  //Default constructor
  constexpr Plane3() = default;

  //Component constructor
  constexpr Plane3(const Vec3<T>& point, const Vec3<T>& normal);

  //Different type copy constructor
  template <typename U>
  constexpr Plane3(const Plane3<U>& plane);

  //Default destructor
  ~Plane3() = default;
};

#include "Plane3.inl"

using Plane3f = Plane3<GLfloat>;
using Plane3d = Plane3<GLdouble>;
