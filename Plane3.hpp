#pragma once

#include "Vec3.hpp"

template <typename T>
class Plane3 {
public:
  Vec3<T> point;
  Vec3<T> normal;

  //Default constructor
  Plane3();

  //Component constructor
  Plane3(const Vec3<T> vector, const Vec3<T> normal);

  //Copy constructor
  Plane3(const Plane3<T>& plane);

  //Different type copy constructor
  template <typename U>
  Plane3(const Plane3<U>& plane);

  //
  ~Plane3();
};

#include "Plane3.inl"

using Plane3f = Plane3<GLfloat>;
using Plane3d = Plane3<GLdouble>;
