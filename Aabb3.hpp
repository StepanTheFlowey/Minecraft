#pragma once

#include "main.hpp"
#include "Vec3.hpp"
#include "Color.hpp"

template <typename T>
class Aabb3 {
public:
  Vec3<T> min;
  Vec3<T> max;

  //Default constructor
  constexpr Aabb3();

  //Vector constructor
  constexpr Aabb3(const Vec3<T> min, const Vec3<T> max);

  //Template copy constructor
  template <typename U>
  constexpr Aabb3(const Aabb3<U>& aabb);

  //Default destructor
  ~Aabb3();

  //
  void set(const Vec3<T> min, const Vec3<T> max);

  //
  bool intersects(const Aabb3<T>) const;

  //Draws axis of box in float
  void draw(const Color color, const float_t offset) const;

  //Draws axis of box in double
  void draw(const Color color, const double_t offset) const;

  //Draws axis of box in float
  void draw(const float_t offset) const;

  //Draws axis of box in double
  void draw(const double_t offset) const;
};

#include "Aabb3.inl"

using Aabb3f = Aabb3<GLfloat>;
using Aabb3d = Aabb3<GLdouble>;
