#pragma once

#include "Vec3.hpp"
#include "Triangle3.hpp"

template <typename T>
class Rect3 {
public:
  Vec3<T> a;
  Vec3<T> b;
  Vec3<T> c;
  Vec3<T> d;

  Rect3();

  Rect3(const Vec3<T> _a, const Vec3<T> _b, const Vec3<T> _c, const Vec3<T> _d);

  ~Rect3();

  T square() const;

  bool isPointInside(const Vec3<T> vector) const;

  Rect3<T> operator+(const Vec3<T> offset) const;

  void operator+=(const Vec3<T> offset);

  static const Rect3<T> Up;
  static const Rect3<T> Down;
  static const Rect3<T> North;
  static const Rect3<T> South;
  static const Rect3<T> West;
  static const Rect3<T> East;
};

#include "Rect3.inl"

using Rect3f = Rect3<GLfloat>;
using Rect3d = Rect3<GLdouble>;
