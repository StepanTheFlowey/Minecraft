#pragma once

#include "Triangle2.hpp"
#include "Math.hpp"

template <typename T>
inline Rect2<T>::Rect2() {

}

template <typename T>
inline Rect2<T>::Rect2(const Vec2<T> _a, const Vec2<T> _b, const Vec2<T> _c, const  Vec2<T> _d) {
  a = _a;
  b = _b;
  c = _c;
  d = _d;
}

template <typename T>
inline Rect2<T>::~Rect2() {

}

template<typename T>
T Rect2<T>::square() const {
  return Triangle2<T>(a, b, c).square() + Triangle2<T>(a, d, c).square();
}

template<typename T>
bool Rect2<T>::isPointInside(const Vec2<T> vector) const {
  return std::abs(
    square() -
    Triangle2<T>(a, b, vector).square() -
    Triangle2<T>(b, c, vector).square() -
    Triangle2<T>(c, d, vector).square() -
    Triangle2<T>(d, a, vector).square()
  ) < 1e-6;
}