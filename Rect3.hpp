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

  //Default constructor
  constexpr Rect3() = default;

  //Component constructor
  constexpr Rect3(
    const Vec3<T>& a,
    const Vec3<T>& b,
    const Vec3<T>& c,
    const Vec3<T>& d
  );

  //Default destructor
  ~Rect3() = default;

  //
  T square() const;

  //
  bool isPointInside(const Vec3<T> point) const;

  //
  Rect3<T> operator+(const Vec3<T> offset) const;

  //
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
