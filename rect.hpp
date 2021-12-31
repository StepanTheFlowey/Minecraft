#pragma once

#include "vec3.hpp"

template <typename T> class Rect {
public:
  Vec3<T> a;
  Vec3<T> b;
  Vec3<T> c;
  Vec3<T> d;

  Rect();

  Rect(Vec3<T> A, Vec3<T> B, Vec3<T> C, Vec3<T> D);

  const Rect<T> operator+(const Vec3<T> offset) const {
    return Rect<T>(A + offset, B + offset, C + offset, D + offset);
  }

  void operator+=(const Vec3<T> offset) {
    A += offset;
    B += offset;
    C += offset;
    D += offset;
  }

  static const Rect<T> Up;
  static const Rect<T> Down;
  static const Rect<T> North;
  static const Rect<T> South;
  static const Rect<T> West;
  static const Rect<T> East;
};

using Rectf = Rect<GLfloat>;
using Rectd = Rect<GLdouble>;

#include "rect.inl"