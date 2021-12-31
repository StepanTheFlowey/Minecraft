#pragma once

#include "types.hpp"
#include "vec3.hpp"
#include "color.hpp"

template <typename T> class Aabb3 {
public:
  Vec3<T> min;
  Vec3<T> max;

  //Default constructor
  Aabb3();

  //Component construtor
  Aabb3(T, T, T, T, T, T);

  //Vector constructor
  Aabb3(const Vec3<T>, const Vec3<T>);

  //Copy constructor
  Aabb3(const Aabb3<T>&);

  //Template copy constructor
  template <typename U>
  Aabb3(const Aabb3<U>&);

  //
  void setComponent(T, T, T, T, T, T);

  //
  void setVector(Vec3<T>, Vec3<T>);

  //
  bool intersects(const Aabb3<T>) const;

  //
  template <typename U>
  bool intersects(const Aabb3<U>) const;

  //
  bool intersects(T, T, T, T, T, T) const;

  //Draws axis of box in float
  void drawColorf(const Color) const;

  //Draws axis of box in double with 
  void drawColord(const Color) const;

  //Draws axis of box in float
  void drawAxisf() const;

  //Draws axis of box in double
  void drawAxisd() const;
};

#include "aabb3.inl"

using Aabb3f = Aabb3<GLfloat>;
using Aabb3d = Aabb3<GLdouble>;