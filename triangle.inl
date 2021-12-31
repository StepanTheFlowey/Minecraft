#pragma once

template <typename T> Triangle<T>::Triangle() {

}

template <typename T> Triangle<T>::Triangle(Vec3<T> a, Vec3<T> b, Vec3<T> c) {
  A = a;
  B = b;
  C = c;
}

template <typename T> template <typename U> Triangle<T>::Triangle(Triangle<U> plane) {
  A = plane.A;
  B = plane.B;
  C = plane.C;
}