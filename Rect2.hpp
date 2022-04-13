#pragma once

#include "Vec2.hpp"

template <typename T>
class Rect2 {
public:
  Vec2<T> a;
  Vec2<T> b;
  Vec2<T> c;
  Vec2<T> d;

  //Default constructor
  Rect2();

  //Component constructor
  Rect2(const Vec2<T> _a, const Vec2<T> _b, const Vec2<T> _c, const  Vec2<T> _d);

  //Default destructor
  ~Rect2();

  //
  T square() const;

  //
  bool isPointInside(const Vec2<T>) const;
};

#include "Rect2.inl"

using Rect2d = Rect2<GLdouble>;
using Rect2f = Rect2<GLfloat>;
