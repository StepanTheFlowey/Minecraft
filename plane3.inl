#pragma once

template <typename T>
inline Plane3<T>::Plane3() {

}

template<typename T>
inline Plane3<T>::Plane3(const Vec3<T> _point, const Vec3<T> _normal) {
  point = _point;
  normal = _normal;
}

template <typename T>
inline Plane3<T>::Plane3(const Plane3<T>& plane) {
  point = plane.point;
  normal = plane.normal;
}

template <typename T> template <typename U>
inline Plane3<T>::Plane3(const Plane3<U>& plane) {
  point = plane.point;
  normal = plane.normal;
}

template <typename T>
inline Plane3<T>::~Plane3() {

}