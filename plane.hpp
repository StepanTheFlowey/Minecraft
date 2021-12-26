#pragma once
#include "vec3.hpp"

template <typename T> class Plane {
public:
  Vec3<T> A;
  Vec3<T> B;
  Vec3<T> C;

  Plane() {

  }

  Plane(Vec3<T> a, Vec3<T> b, Vec3<T> c) {
    A = a;
    B = b;
    C = c;
  }
  
  template <typename U> Plane(Plane<U> plane) {
    A = plane.A;
    B = plane.B;
    C = plane.C;
  }
};

using Planed = Plane<GLdouble>;
using Planef = Plane<GLfloat>;