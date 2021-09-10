#pragma once
#include <SFML\System\Vector2.hpp>

template <typename T> class Vec2 {
public:
  T x = 0;
  T y = 0;

  Vec2() {

  }

  template <typename U>Vec2(sf::Vector2<U> vec) {
    x = static_cast<T>(vec.x);
    y = static_cast<U>(vec.y);
  }

  Vec2(T X, T Y) {
    x = X;
    y = Y;
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

  Vec3():x(0),y(0),z(0) {

  }

  Vec3(T X, T Y, T Z) {
    x = X;
    y = Y;
    z = Z;
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