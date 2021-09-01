#include "Point.hpp"
#pragma once

template<typename T> class Rect2 {
public:
  T x;
  T y;
  T width;
  T height;

  Rect2() {

  }

  Rect2(T X, T Y, T Width, T Height) {
    x = X;
    y = Y;
    width = Width;
    height = Height;
  }
};

template<typename T> class Rect3 {
public:
  T x;
  T y;
  T z;
  T width;
  T height;
  T depth;

  Rect3() {

  }

  Rect3(T X, T Y, T Z, T Width, T Height, T Depth) {
    x = X;
    y = Y;
    z = Z;
    width = Width;
    height = Height;
    depth = Depth;
  }

  constexpr bool checkCollide(Rect3<T> &r) {
    return 
  }

  template<typename U> operator Rect3<U>() {
    return Rect3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(width), static_cast<U>(height), static_cast<U>(depth));
  }
};