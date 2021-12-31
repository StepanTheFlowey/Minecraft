#pragma once

template <typename T> Rect<T>::Rect() {

}

template <typename T> Rect<T>::Rect(Vec3<T> a, Vec3<T> b, Vec3<T> c, Vec3<T> d) {
  A = a;
  B = b;
  C = c;
  D = d;
}

template <typename T> const Rect<T> Rect<T>::Up(
  Vec3<T>(1, 1, 0),
  Vec3<T>(0, 1, 0),
  Vec3<T>(0, 1, 1),
  Vec3<T>(1, 1, 1)
);

template <typename T> const Rect<T> Rect<T>::Down(
  Vec3<T>(1, 0, 0),
  Vec3<T>(0, 0, 0),
  Vec3<T>(0, 0, 1),
  Vec3<T>(1, 0, 1)
);

template <typename T> const Rect<T> Rect<T>::North(
  Vec3<T>(0, 1, 0),
  Vec3<T>(0, 0, 0),
  Vec3<T>(0, 0, 1),
  Vec3<T>(0, 1, 1)
);

template <typename T> const Rect<T> Rect<T>::South(
  Vec3<T>(1, 1, 0),
  Vec3<T>(1, 0, 0),
  Vec3<T>(1, 0, 1),
  Vec3<T>(1, 1, 1)
);

template <typename T> const Rect<T> Rect<T>::West(
  Vec3<T>(0, 1, 1),
  Vec3<T>(0, 0, 1),
  Vec3<T>(1, 0, 1),
  Vec3<T>(1, 1, 1)
);

template <typename T> const Rect<T> Rect<T>::East(
  Vec3<T>(0, 1, 0),
  Vec3<T>(0, 0, 0),
  Vec3<T>(1, 0, 0),
  Vec3<T>(1, 1, 0)
);