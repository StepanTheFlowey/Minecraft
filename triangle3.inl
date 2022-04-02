#pragma once

template <typename T>
inline Triangle3<T>::Triangle3() {

}

template <typename T>
inline Triangle3<T>::Triangle3(const Vec3<T> _a, const Vec3<T> _b, const Vec3<T> _c) {
  a = _a;
  b = _b;
  c = _c;
}

template <typename T> template <typename U>
inline Triangle3<T>::Triangle3(const Triangle3<U>& triangle) {
  a = triangle.a;
  b = triangle.b;
  c = triangle.c;
}

template <typename T>
inline Triangle3<T>::~Triangle3() {

}

template <typename T>
Vec3<T> Triangle3<T>::getNormal() const {
  return Vec3<T>(c - a).vectorProduct(b - a);
}

template <typename T>
T Triangle3<T>::square() const {
  T A = a.distanceTo(b);
  T B = b.distanceTo(c);
  T C = c.distanceTo(a);
  T P = (A + B + C) / 2;
  return sqrt(P * (P - A) * (P - B) * (P - C));
}

template <typename T>
bool Triangle3<T>::isPointInside(const Vec3<T> vector, const Vec3<T> normal) const {
  if(Vec3<T>(b - a).vectorProduct(vector - a).dot(normal) < 1e-10)      return false;
  if(Vec3<T>(vector - a).vectorProduct(c - a).dot(normal) < 1e-10)      return false;
  if(Vec3<T>(b - vector).vectorProduct(c - vector).dot(normal) < 1e-10) return false;
  return true;
}
