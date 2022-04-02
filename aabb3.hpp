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
  Aabb3();

  //Vector constructor
  Aabb3(const Vec3<T> _min, const Vec3<T> _max);

  //Copy constructor
  Aabb3(const Aabb3<T>& aabb);

  //Template copy constructor
  template <typename U>
  Aabb3(const Aabb3<U>& aabb);

  //
  ~Aabb3();

  //
  void set(const Vec3<T> _min, const Vec3<T> _max);

  //
  bool intersects(const Aabb3<T>) const;

  //Draws axis of box in float
  void drawAxisColorf(const Color color, const float_t offset) const;

  //Draws axis of box in double
  void drawAxisColord(const Color color, const double_t offset) const;

  //Draws axis of box in float
  void drawAxisf(const float_t offset) const;

  //Draws axis of box in double
  void drawAxisd(const double_t offset) const;
};

#include "Aabb3.inl"

using Aabb3f = Aabb3<GLfloat>;
using Aabb3d = Aabb3<GLdouble>;
