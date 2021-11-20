#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <iostream>

template <typename T> class Vec2 {
public:
  T x;
  T y;

  Vec2() {
    x = 0;
    y = 0;
  }


  Vec2(T X, T Y) {
    x = X;
    y = Y;
  }

  template <typename U> Vec2(Vec2<U> vec) {
    x = static_cast<T>(vec.x);
    y = static_cast<T>(vec.y);
  }

  template <typename U> Vec2(sf::Vector2<U> vec) {
    x = static_cast<T>(vec.x);
    y = static_cast<T>(vec.y);
  }

  void print() {
    std::wcout << L"X: " << x << L" Y: " << y << std::endl;
  }

  void print(std::wstring str) {
    std::wcout << str << L" X: " << x << L" Y: " << y << std::endl;
  }

  Vec2<T> operator+(const Vec2<T> &r) {
    return Vec2<T>(x + r.x, y + r.y);
  }

  template <typename U> Vec2<T> operator+(const  Vec2<U> &r) {
    return Vec2<T>(x + static_cast<T>(r.x), y + static_cast<T>(r.y));
  }

  Vec2<T> operator-(const Vec2<T> &r) {
    return Vec2<T>(x - r.x, y - r.y);
  }

  template <typename U> Vec2<T> operator-(const Vec2<U> &r) {
    return Vec2<T>(x - static_cast<T>(r.x), y - static_cast<T>(r.y));
  }

  Vec2<T> operator*(const T r) {
    return Vec2<T>(x * r, y * r);
  }

  Vec2<T> operator*(const Vec2<T> &r) {
    return Vec2<T>(x * r.x, y * r.y);
  }

  template <typename U> Vec2<T> operator*(const Vec2<U> &r) {
    return Vec2<T>(x * static_cast<T>(r.x), y * static_cast<T>(r.y));
  }

  Vec2<T> operator/(const T r) {
    return Vec2<T>(x / r, y / r);
  }

  Vec2<T> operator/(const Vec2<T> &r) {
    return Vec2<T>(x / r.x, y / r.y);
  }

  template <typename U> Vec2<T> operator/(const Vec2<U> &r) {
    return Vec2<T>(x / static_cast<T>(r.x), y / static_cast<T>(r.y));
  }

  Vec2<T> operator%(const T r) {
    return Vec2<T>(x % r, y % r);
  }

  Vec2<T> operator%(const Vec2<T> &r) {
    return Vec2<T>(x % r.x, y % r.y);
  }

  template <typename U> Vec2<T> operator%(const Vec2<U> &r) {
    return Vec2<T>(x % static_cast<T>(r.x), y % static_cast<T>(r.y));
  }

  void operator=(const Vec2<T> &r) {
    x = r.x;
    y = r.y;
  }

  template<typename U> void operator=(const Vec2<U> &r) {
    x = static_cast<T>(r.x);
    y = static_cast<T>(r.y);
  }

  void operator+=(const Vec2<T> &r) {
    x += r.x;
    y += r.y;
  }

  template<typename U> void operator+=(const Vec2<U> &r) {
    x += static_cast<T>(r.x);
    y += static_cast<T>(r.y);
  }

  void operator-=(const Vec2<T> &r) {
    x -= r.x;
    y -= r.y;
  }

  template<typename U> void operator-=(const Vec2<U> &r) {
    x -= static_cast<T>(r.x);
    y -= static_cast<T>(r.y);
  }

  void operator*=(const T r) {
    x *= r;
    y *= r;
  }

  void operator*=(const Vec2<T> &r) {
    x *= r.x;
    y *= r.y;
  }

  template<typename U> void operator*=(const Vec2<U> &r) {
    x *= static_cast<T>(r.x);
    y *= static_cast<T>(r.y);
  }

  void operator/=(const T r) {
    x /= r;
    y /= r;
  }

  void operator/=(const Vec2<T> &r) {
    x /= r.x;
    y /= r.y;
  }

  template<typename U> void operator/=(const Vec2<U> &r) {
    x /= static_cast<T>(r.x);
    y /= static_cast<T>(r.y);
  }

  void operator%=(const T r) {
    x %= r;
    y %= r;
  }

  void operator%=(const Vec2<T> &r) {
    x %= r.x;
    y %= r.y;
  }

  template<typename U> void operator%=(const Vec2<U> &r) {
    x %= static_cast<T>(r.x);
    y %= static_cast<T>(r.y);
  }
};

template <typename T> class Vec3 {
public:
  T x;
  T y;
  T z;

  Vec3() {
    x = 0;
    y = 0;
    z = 0;
  }

  Vec3(T X, T Y, T Z) {
    x = X;
    y = Y;
    z = Z;
  }

  template <typename U> Vec3(Vec3<U> vec) {
    x = static_cast<T>(vec.x);
    y = static_cast<T>(vec.y);
    z = static_cast<T>(vec.z);
  }

  void print() const {
    std::wcout << L"X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
  }

  void print(std::wstring str) const {
    std::wcout << str << L" X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
  }

  Vec3<T> abs() {
    return Vec3<T>(std::abs(x), std::abs(y), std::abs(z));
  }

  double_t lenght() {
    return std::sqrt(x * x + y * y + z * z);
  }

  Vec3<T> normalize() {
    const T l = lenght();
    return Vec3<T>(x / l, y / l, z / l);
  }

  double_t distanceTo(Vec3<T> point) {
    T X = x - point.x;
    T Y = y - point.y;
    T Z = z - point.z;
    return std::sqrt(X * X + Y * Y + Z * Z);
  }

  inline void glVertex() {
    glVertex3d(static_cast<GLdouble>(x),
               static_cast<GLdouble>(y),
               static_cast<GLdouble>(z));
  }

  bool operator==(const Vec3<T> &r) {
    return x == r.x && y == r.y && z == r.z;
  }

  bool operator!=(const Vec3<T> &r) {
    return x != r.x || y != r.y || z != r.z;
  }

  Vec3<T> operator+(const Vec3<T> &r) {
    return Vec3<T>(x + r.x, y + r.y, z + r.z);
  }

  template <typename U> Vec3<T> operator+(const  Vec3<U> &r) {
    return Vec3<T>(x + static_cast<T>(r.x), y + static_cast<T>(r.y), z + static_cast<T>(r.z));
  }

  Vec3<T> operator-(const Vec3<T> &r) {
    return Vec3<T>(x - r.x, y - r.y, z - r.z);
  }

  template <typename U> Vec3<T> operator-(const Vec3<U> &r) {
    return Vec3<T>(x - static_cast<T>(r.x), y - static_cast<T>(r.y), z - static_cast<T>(r.z));
  }

  Vec3<T> operator*(const T r) {
    return Vec3<T>(x * r, y * r, z * r);
  }

  Vec3<T> operator*(const Vec3<T> &r) {
    return Vec3<T>(x * r.x, y * r.y, z * r.z);
  }

  template <typename U> Vec3<T> operator*(const Vec3<U> &r) {
    return Vec3<T>(x * static_cast<T>(r.x), y * static_cast<T>(r.y), z * static_cast<T>(r.z));
  }

  Vec3<T> operator/(const T r) {
    return Vec3<T>(x / r, y / r, z / r);
  }

  Vec3<T> operator/(const Vec3<T> &r) {
    return Vec3<T>(x / r.x, y / r.y, z / r.z);
  }

  template <typename U> Vec3<T> operator/(const Vec3<U> &r) {
    return Vec3<T>(x / static_cast<T>(r.x), y / static_cast<T>(r.y), z / static_cast<T>(r.z));
  }

  Vec3<T> operator%(const T r) {
    return Vec3<T>(x % r, y % r, z % r);
  }

  Vec3<T> operator%(const Vec3<T> &r) {
    return Vec3<T>(x % r.x, y % r.y, z % r.z);
  }

  template <typename U> Vec3<T> operator%(const Vec3<U> &r) {
    return Vec3<T>(x % static_cast<T>(r.x), y % static_cast<T>(r.y), z % static_cast<T>(r.z));
  }

  void operator=(const Vec3<T> &r) {
    x = r.x;
    y = r.y;
    z = r.z;
  }

  template<typename U> void operator=(const Vec3<U> &r) {
    x = static_cast<T>(r.x);
    y = static_cast<T>(r.y);
    z = static_cast<T>(r.z);
  }

  void operator+=(const Vec3<T> &r) {
    x += r.x;
    y += r.y;
    z += r.z;
  }

  template<typename U> void operator+=(const Vec3<U> &r) {
    x += static_cast<T>(r.x);
    y += static_cast<T>(r.y);
    z += static_cast<T>(r.z);
  }

  void operator-=(const Vec3<T> &r) {
    x -= r.x;
    y -= r.y;
    z -= r.z;
  }

  template<typename U> void operator-=(const Vec3<U> &r) {
    x -= static_cast<T>(r.x);
    y -= static_cast<T>(r.y);
    z -= static_cast<T>(r.z);
  }

  void operator*=(const T r) {
    x *= r;
    y *= r;
    z *= r;
  }

  void operator*=(const Vec3<T> &r) {
    x *= r.x;
    y *= r.y;
    z *= r.z;
  }

  template<typename U> void operator*=(const Vec3<U> &r) {
    x *= static_cast<T>(r.x);
    y *= static_cast<T>(r.y);
    z *= static_cast<T>(r.z);
  }

  void operator/=(const T r) {
    x /= r;
    y /= r;
    z /= r;
  }

  void operator/=(const Vec3<T> &r) {
    x /= r.x;
    y /= r.y;
    z /= r.z;
  }

  template<typename U> void operator/=(const Vec3<U> &r) {
    x /= r.x;
    y /= r.y;
    z /= r.z;
  }

  void operator%=(const T r) {
    x %= r;
    y %= r;
    z %= r;
  }

  void operator%=(const Vec3<T> &r) {
    x %= r.x;
    y %= r.y;
    z %= r.z;
  }

  template<typename U> void operator%=(const Vec3<U> &r) {
    x %= r.x;
    y %= r.y;
    z %= r.z;
  }
};