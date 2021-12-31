#pragma once

#include "vec2.hpp"

template <typename T> class Rect2 {
public:
  Vec2<T> a;
  Vec2<T> b;
  Vec2<T> c;
  Vec2<T> d;

  //
  Rect2();

  //
  Rect2(const Vec2<T>, const Vec2<T>, const Vec2<T>, const Vec2<T>);

  //
  template <typename U>
  Rect2(const Vec2<U>, const Vec2<U>, const Vec2<U>, const Vec2<U>);

  //
  Rect2(const Rect2<T>&);

  //
  template <typename U>
  Rect2(const Rect2<U>&);

  //
  T square() const;

  //
  bool isPointInside(const Vec2<T>) const;
};

#include "rect2.inl"

using Rect2d = Rect2<GLdouble>;
using Rect2f = Rect2<GLfloat>;