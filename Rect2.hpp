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
  constexpr Rect2() = default;

  //Component constructor
  constexpr Rect2(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c, const  Vec2<T>& d);

  //Default destructor
  ~Rect2() = default;

  //
  T square() const;

  //
  bool isPointInside(const Vec2<T>& point) const;
};

#include "Rect2.inl"

using Rect2d = Rect2<GLdouble>;
using Rect2f = Rect2<GLfloat>;
