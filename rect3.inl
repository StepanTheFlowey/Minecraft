#pragma once

template <typename T>
inline Rect3<T>::Rect3() {

}

template <typename T>
inline Rect3<T>::Rect3(const Vec3<T> _a, const Vec3<T> _b, const Vec3<T> _c, const Vec3<T> _d) {
  a = _a;
  b = _b;
  c = _c;
  d = _d;
}

template <typename T>
inline Rect3<T>::~Rect3() {

}

template <typename T>
T Rect3<T>::square() const {
  return Triangle3<T>(a, b, c).square() + Triangle3<T>(a, d, c).square();
}

template <typename T>
bool Rect3<T>::isPointInside(const Vec3<T> vector) const {
  return
    Rect2<T>(a.cutX(), b.cutX(), c.cutX(), d.cutX()).isPointInside(vector.cutX()) &&
    Rect2<T>(a.cutY(), b.cutY(), c.cutY(), d.cutY()).isPointInside(vector.cutY()) &&
    Rect2<T>(a.cutZ(), b.cutZ(), c.cutZ(), d.cutZ()).isPointInside(vector.cutZ());
}

template <typename T>
inline Rect3<T> Rect3<T>::operator+(const Vec3<T> offset) const {
  return Rect3<T>(a + offset, b + offset, c + offset, d + offset);
}

template <typename T>
inline void Rect3<T>::operator+=(const Vec3<T> offset) {
  a += offset;
  b += offset;
  c += offset;
  d += offset;
}

template <typename T>
const Rect3<T> Rect3<T>::Up(
  Vec3<T>(1, 1, 0),
  Vec3<T>(0, 1, 0),
  Vec3<T>(0, 1, 1),
  Vec3<T>(1, 1, 1)
);

template <typename T>
const Rect3<T> Rect3<T>::Down(
  Vec3<T>(1, 0, 0),
  Vec3<T>(1, 0, 1),
  Vec3<T>(0, 0, 1),
  Vec3<T>(0, 0, 0)
);

template <typename T>
const Rect3<T> Rect3<T>::North(
  Vec3<T>(0, 1, 0),
  Vec3<T>(0, 0, 0),
  Vec3<T>(0, 0, 1),
  Vec3<T>(0, 1, 1)
);

template <typename T>
const Rect3<T> Rect3<T>::South(
  Vec3<T>(1, 1, 1),
  Vec3<T>(1, 0, 1),
  Vec3<T>(1, 0, 0),
  Vec3<T>(1, 1, 0)
);

template <typename T>
const Rect3<T> Rect3<T>::West(
  Vec3<T>(0, 1, 1),
  Vec3<T>(0, 0, 1),
  Vec3<T>(1, 0, 1),
  Vec3<T>(1, 1, 1)
);

template <typename T>
const Rect3<T> Rect3<T>::East(
  Vec3<T>(1, 1, 0),
  Vec3<T>(1, 0, 0),
  Vec3<T>(0, 0, 0),
  Vec3<T>(0, 1, 0)
);