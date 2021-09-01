#pragma once

template <typename T> class Point2 {

public:
  T x = 0;
  T y = 0;

  Point2() {

  }

  Point2(T X, T Y) {
    x = X;
    y = Y;
  }

  Point2<T> operator+(const Point2<T> &r) {
    return Point2<T>(x + r.x, y + r.y);
  }

  template <typename U> Point2<T> operator+(const  Point2<U> &r) {
    return Point2<T>(x + static_cast<T>(r.x), y + static_cast<T>(r.y));
  }

  Point2<T> operator-(const Point2<T> &r) {
    return Point2<T>(x - r.x, y - r.y);
  }

  template <typename U> Point2<T> operator-(const Point2<U> &r) {
    return Point2<T>(x - static_cast<T>(r.x), y - static_cast<T>(r.y));
  }

  Point2<T> operator*(const Point2<T> &r) {
    return Point2<T>(x * r.x, y * r.y);
  }

  template <typename U> Point2<T> operator*(const Point2<U> &r) {
    return Point2<T>(x * static_cast<T>(r.x), y * static_cast<T>(r.y));
  }

  Point2<T> operator/(const Point2<T> &r) {
    return Point2<T>(x / r.x, y / r.y);
  }

  template <typename U> Point2<T> operator/(const Point2<U> &r) {
    return Point2<T>(x / static_cast<T>(r.x), y / static_cast<T>(r.y));
  }

  void operator=(const Point2<T> &r) {
    x = r.x;
    y = r.y;
  }

  template<typename U> void operator=(const Point2<U> &r) {
    x = static_cast<T>(r.x);
    y = static_cast<T>(r.y);
  }

  void operator+=(const Point2<T> &r) {
    x += r.x;
    y += r.y;
  }

  template<typename U> void operator+=(const Point2<U> &r) {
    x += static_cast<T>(r.x);
    y += static_cast<T>(r.y);
  }

  void operator-=(const Point2<T> &r) {
    x -= r.x;
    y -= r.y;
  }

  template<typename U> void operator-=(const Point2<U> &r) {
    x -= static_cast<T>(r.x);
    y -= static_cast<T>(r.y);
  }

  void operator*=(const Point2<T> &r) {
    x *= r.x;
    y *= r.y;
  }

  template<typename U> void operator*=(const Point2<U> &r) {
    x *= static_cast<T>(r.x);
    y *= static_cast<T>(r.y);
  }

  void operator/=(const Point2<T> &r) {
    x /= r.x;
    y /= r.y;
  }

  template<typename U> void operator/=(const Point2<U> &r) {
    x /= static_cast<T>(r.x);
    y /= static_cast<T>(r.y);
  }
};

template <typename T> class Point3 {

public:
  T x = 0;
  T y = 0;
  T z = 0;

  Point3() {

  }

  Point3(T X, T Y, T Z) {
    x = X;
    y = Y;
    z = Z;
  }

  Point3<T> operator+(const Point3<T> &r) {
    return Point3<T>(x + r.x, y + r.y, z + r.z);
  }

  template <typename U> Point3<T> operator+(const  Point3<U> &r) {
    return Point3<T>(x + static_cast<T>(r.x), y + static_cast<T>(r.y), z + static_cast<T>(r.z));
  }

  Point3<T> operator-(const Point3<T> &r) {
    return Point3<T>(x - r.x, y - r.y, z - r.z);
  }

  template <typename U> Point3<T> operator-(const Point3<U> &r) {
    return Point3<T>(x - static_cast<T>(r.x), y - static_cast<T>(r.y), z - static_cast<T>(r.z));
  }

  Point3<T> operator*(const Point3<T> &r) {
    return Point3<T>(x * r.x, y * r.y, z * r.z);
  }

  template <typename U> Point3<T> operator*(const Point3<U> &r) {
    return Point3<T>(x * static_cast<T>(r.x), y * static_cast<T>(r.y), z * static_cast<T>(r.z));
  }

  Point3<T> operator/(const Point3<T> &r) {
    return Point3<T>(x / r.x, y / r.y, z / r.z);
  }

  template <typename U> Point3<T> operator/(const Point3<U> &r) {
    return Point3<T>(x / static_cast<T>(r.x), y / static_cast<T>(r.y), z / static_cast<T>(r.z));
  }

  void operator=(const Point3<T> &r) {
    x = r.x;
    y = r.y;
    z = r.z;
  }

  template<typename U> void operator=(const Point3<U> &r) {
    x = static_cast<T>(r.x);
    y = static_cast<T>(r.y);
    z = static_cast<T>(r.z);
  }

  void operator+=(const Point3<T> &r) {
    x += r.x;
    y += r.y;
    z += r.z;
  }

  template<typename U> void operator+=(const Point3<U> &r) {
    x += static_cast<T>(r.x);
    y += static_cast<T>(r.y);
    z += static_cast<T>(r.z);
  }

  void operator-=(const Point3<T> &r) {
    x -= r.x;
    y -= r.y;
    z -= r.z;
  }

  template<typename U> void operator-=(const Point3<U> &r) {
    x -= static_cast<T>(r.x);
    y -= static_cast<T>(r.y);
    z -= static_cast<T>(r.z);
  }

  void operator*=(const Point3<T> &r) {
    x *= r.x;
    y *= r.y;
    z *= r.z;
  }

  template<typename U> void operator*=(const Point3<U> &r) {
    x *= static_cast<T>(r.x);
    y *= static_cast<T>(r.y);
    z *= static_cast<T>(r.z);
  }

  void operator/=(const Point3<T> &r) {
    x /= r.x;
    y /= r.y;
    z /= r.z;
  }
};