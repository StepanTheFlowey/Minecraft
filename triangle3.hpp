#pragma once

#include "Vec3.hpp"

template <typename T>
class Triangle3 {
public:
  Vec3<T> a;
  Vec3<T> b;
  Vec3<T> c;

  //Default constructor
  Triangle3();

  //Component constructor
  Triangle3(const Vec3<T> _a, const Vec3<T> _b, const Vec3<T> _c);

  //Different type copy constructor
  template <typename U>
  Triangle3(const Triangle3<U>& triangle);

  //Default destructor
  ~Triangle3();

  //
  Vec3<T> getNormal() const;

  //
  T square() const;

  //
  bool isPointInside(const Vec3<T> vector, const Vec3<T> normal = getNormal()) const;
};

#include "Triangle3.inl"

using Triangle3d = Triangle3<GLdouble>;
using Triangle3f = Triangle3<GLfloat>;