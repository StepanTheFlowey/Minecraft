#pragma once

#include "vec3.hpp"

template <typename T> class Triangle3 {
public:
  Vec3<T> a;
  Vec3<T> b;
  Vec3<T> c;

  //Default constructor
  Triangle3();

  //Component constructor
  Triangle3(Vec3<T>, Vec3<T>, Vec3<T>);

  //Copy constructor
  Triangle3(const Triangle3<T>&);

  //Different type copy constructor
  template <typename U>
  Triangle3(const Triangle3<U>&);

  //
  Vec3<T> getNormal() const;

  //
  T square() const;

  //
  bool isPointInside(const Vec3<T>, const Vec3<T> = getNormal());
};

#include "triangle3.inl"

using Triangle3d = Triangle3<GLdouble>;
using Triangle3f = Triangle3<GLfloat>;