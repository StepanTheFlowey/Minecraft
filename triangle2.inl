#pragma once

#include "triangle2.hpp"

template <typename T>
inline Triangle2<T>::Triangle2() {

}

template <typename T>
inline Triangle2<T>::Triangle2(const Vec2<T> _a, const Vec2<T> _b, const Vec2<T> _c) {
  a = _a;
  b = _b;
  c = _c;
}

template <typename T> template <typename U>
inline Triangle2<T>::Triangle2(const Vec2<U> _a, const Vec2<U> _b, const Vec2<U> _c) {
  a = _a;
  b = _b;
  c = _c;
}

template <typename T>
inline Triangle2<T>::Triangle2(const Triangle2<T>& triangle) {
  a = triangle.a;
  b = triangle.b;
  c = triangle.c;
}

template <typename T> template <typename U>
inline Triangle2<T>::Triangle2(const Triangle2<U>& triangle) {
  a = triangle.a;
  b = triangle.b;
  c = triangle.c;
}

template<typename T>
inline T Triangle2<T>::square() const {
  T A = a.distanceTo(b);
  T B = b.distanceTo(c);
  T C = c.distanceTo(a);
  T P = (A + B + C) / 2;
  return sqrt(P * (P - A) * (P - B) * (P - C));
}

//HACK: this
template<typename T>
inline bool Triangle2<T>::isPointInside(const Vec2<T>) const {
  return false;
}