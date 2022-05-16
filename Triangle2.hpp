#pragma once

#include "Vec2.hpp"

template <typename T>
class Triangle2 {
public:
  Vec2<T> a;
  Vec2<T> b;
  Vec2<T> c;

  //Default constructor
  Triangle2();

  //
  Triangle2(const Vec2<T>, const Vec2<T>, const Vec2<T>);

  //
  template <typename U>
  Triangle2(const Triangle2<U>&);

  //Default destructor
  ~Triangle2();

  //
  T square() const;

  //
  bool isPointInside(const Vec2<T>) const;
};

#include "Triangle2.inl"

using Triangle2d = Triangle2<GLdouble>;
using Triangle2f = Triangle2<GLfloat>;
