#pragma once
#include "vec.hpp"

template <typename T> class Plane {
public:
  T x;
  T y;
  T z;
  T vX;
  T vY;
  T vZ;

  Plane():x(0), y(0), z(0), vX(0), vY(0), vZ(0) {

  }

  Plane(T X,T Y,T Z,T VX,T VY,T VZ) {
    x = X;
    y = Y;
    z = Z;
    vX = VX;
    vY = VY;
    vZ = VZ;

  }

  template <typename U> Plane(Plane<U> &plane) {
    x = plane.x;
    y = plane.y;
    z = plane.z;
    vX = plane.vX;
    vY = plane.vY;
    vZ = plane.vZ;
  }
};