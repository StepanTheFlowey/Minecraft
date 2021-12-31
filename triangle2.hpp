#pragma once

#include "vec2.hpp"

template <typename T> class Triangle2 {
public:
  Vec2<T> a;
  Vec2<T> b;
  Vec2<T> c;

  //
  Triangle2();

  //
  Triangle2(const Vec2<T>, const Vec2<T>, const Vec2<T>);

  //
  template <typename U>
  Triangle2(const Vec2<U>, const Vec2<U>, const Vec2<U>);

  //
  Triangle2(const Triangle2<T>&);

  //
  template <typename U>
  Triangle2(const Triangle2<U>&);

  //
  T square() const;

  //
  bool isPointInside(const Vec2<T>) const;
};

#include "triangle2.inl"

using Triangle2d = Triangle2<GLdouble>;
using Triangle2f = Triangle2<GLfloat>;