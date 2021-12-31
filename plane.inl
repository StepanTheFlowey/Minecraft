#pragma once

template <typename T> Plane<T>::Plane() {

}

template <typename T> Plane<T>::Plane(const Plane<T>& plane) {
  point = plane.point;
  normal = plane.normal;
}

template <typename T> typename <template U> Plane<T>::Plane(const Plane<U>& plane) {

}