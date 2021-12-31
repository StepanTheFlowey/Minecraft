#pragma once

#include "triangle3.hpp"

template <typename T>
inline Triangle3<T>::Triangle3() {

}

template <typename T>
inline Triangle3<T>::Triangle3(Vec3<T> A, Vec3<T> B, Vec3<T> C) {
  a = A;
  b = B;
  c = C;
}

template <typename T>
inline Triangle3<T>::Triangle3(const Triangle3<T>& triangle) {
  a = triangle.a;
  b = triangle.b;
  c = triangle.c;
}

template <typename T> template <typename U>
inline Triangle3<T>::Triangle3(const Triangle3<U>& triangle) {
  a = triangle.a;
  b = triangle.b;
  c = triangle.c;
}

template<typename T>
inline Vec3<T> Triangle3<T>::getNormal() const {
  return Vec3<T>(c - a).vectorProduct(b - a);
}

template <typename T>
inline T Triangle3<T>::square() const {
  T A = a.distanceTo(b);
  T B = b.distanceTo(c);
  T C = c.distanceTo(a);
  T P = (A + B + C) / 2;
  return sqrt(P * (P - A) * (P - B) * (P - C));
}

template <typename T>
inline bool Triangle3<T>::isPointInside(const Vec3<T> vector, const Vec3<T> normal) {
  if(Vec3<T>(b - a).vectorProduct(vector - a).dot(normal) < 1e-10)
    return false;
  if(Vec3<T>(vector - a).vectorProduct(c - a).dot(normal) < 1e-10)
    return false;
  if(Vec3<T>(b - vector).vectorProduct(c - vector).dot(normal) < 1e-10)
    return false;
  return true;
}