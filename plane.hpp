#pragma once

#include "vec3.hpp"

template <typename T> class Plane {
public:
  Vec3<T> point;
  Vec3<T> normal;

  //Default constructor
  Plane();

  //Copy constructor
  Plane(const Plane<T>&);

  //Different type copy constructor
  template <typename U> Plane(const Plane<U>&);
};

#include "plane.inl"