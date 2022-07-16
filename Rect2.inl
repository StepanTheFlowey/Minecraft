#pragma once

#include "Triangle2.hpp"
#include "Math.hpp"

template <typename T>
constexpr Rect2<T>::Rect2(const Vec2<T>& _a, const Vec2<T>& _b, const Vec2<T>& _c, const Vec2<T>& _d) {
  a = _a;
  b = _b;
  c = _c;
  d = _d;
}

template<typename T>
T Rect2<T>::square() const {
  return Triangle2<T>(a, b, c).square() + Triangle2<T>(a, d, c).square();
}

template<typename T>
bool Rect2<T>::isPointInside(const Vec2<T>& point) const {
  return std::abs(
    square() -
    Triangle2<T>(a, b, point).square() -
    Triangle2<T>(b, c, point).square() -
    Triangle2<T>(c, d, point).square() -
    Triangle2<T>(d, a, point).square()
  ) < 1e-6;
}
