#pragma once

template<typename T>
constexpr Plane3<T>::Plane3(const Vec3<T>& _point, const Vec3<T>& _normal) {
  point = _point;
  normal = _normal;
}

template <typename T> template <typename U>
constexpr Plane3<T>::Plane3(const Plane3<U>& plane) {
  point = plane.point;
  normal = plane.normal;
}
