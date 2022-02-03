#pragma once

#include "vec2.hpp"

template <typename T>
inline Vec2<T>::Vec2() {
  x = 0;
  y = 0;
}

template <typename T>
inline Vec2<T>::Vec2(T X, T Y) {
  x = X;
  y = Y;
}

template <typename T>
inline Vec2<T>::Vec2(const Vec2<T>& vector) {
  x = vector.x;
  y = vector.y;
}

template <typename T> template <typename U>
inline Vec2<T>::Vec2(const Vec2<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
}

template <typename T>
inline Vec2<T>::Vec2(const sf::Vector2<T>& vector) {
  x = vector.x;
  y = vector.y;
}

template <typename T> template <typename U>
inline Vec2<T>::Vec2(const sf::Vector2<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
}

template <typename T>
inline void Vec2<T>::print() const {
  std::cout << "X: " << x << " Y: " << y << std::endl;
}

template <typename T>
inline void Vec2<T>::print(std::string string) const {
  std::cout << string << " X: " << x << " Y: " << y << std::endl;
}

template <typename T>
inline void Vec2<T>::wprint() const {
  std::wcout << L"X: " << x << L" Y: " << y << std::endl;
}

template <typename T>
inline void Vec2<T>::wprint(std::wstring string) const {
  std::wcout << string << L" X: " << x << L" Y: " << y << std::endl;
}

template <typename T>
inline Vec2<T> Vec2<T>::abs() const {
  return Vec2<T>(std::abs(x), abs(y));
}

template <typename T>
inline double_t Vec2<T>::lenght() const {
  return std::sqrt(x * x + y * y);
}

template <typename T>
inline Vec2<T> Vec2<T>::normalize() const {
  const T l = lenght();
  return Vec2<T>(x / l, y / l);
}

template <typename T>
inline double_t Vec2<T>::distanceTo(Vec2<T> vector) const {
  T X = x - vector.x;
  T Y = y - vector.y;
  return std::sqrt(X * X + Y * Y);
}

template <typename T>
inline void Vec2<T>::glVertex() const {
  glVertex2d(
    static_cast<GLdouble>(x),
    static_cast<GLdouble>(y)
  );
}

template <typename T>
inline Vec2<T> Vec2<T>::operator+(const T scalar)const {
  return Vec2<T>(x + scalar, y + scalar);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator+(const U scalar) const {
  return Vec2<T>(x + static_cast<T>(scalar), y + static_cast<T>(scalar));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator+(const Vec2<T>& vector) const {
  return Vec2<T>(x + vector.x, y + vector.y);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator+(const  Vec2<U>& vector) const {
  return Vec2<T>(x + static_cast<T>(vector.x), y + static_cast<T>(vector.y));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator-(const T scalar)const {
  return Vec2<T>(x - scalar, y - scalar);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator-(const U scalar) const {
  return Vec2<T>(x - static_cast<T>(scalar), y - static_cast<T>(scalar));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator-(const Vec2<T>& vector) const {
  return Vec2<T>(x - vector.x, y - vector.y);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator-(const Vec2<U>& vector) const {
  return Vec2<T>(x - static_cast<T>(vector.x), y - static_cast<T>(vector.y));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator*(const T scalar) const {
  return Vec2<T>(x * scalar, y * scalar);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator*(const U scalar) const {
  return Vec2<T>(x * static_cast<T>(scalar), y * static_cast<T>(scalar));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator*(const Vec2<T>& vector) const {
  return Vec2<T>(x * vector.x, y * vector.y);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator*(const Vec2<U>& vector) const {
  return Vec2<T>(x * static_cast<T>(vector.x), y * static_cast<T>(vector.y));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator/(const T scalar) const {
  return Vec2<T>(x / scalar, y / scalar);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator/(const U scalar) const {
  return Vec2<T>(x / static_cast<T>(scalar), y / static_cast<T>(scalar));
}

template <typename T>

inline Vec2<T> Vec2<T>::operator/(const Vec2<T>& vector) const {
  return Vec2<T>(x / vector.x, y / vector.y);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator/(const Vec2<U>& vector) const {
  return Vec2<T>(x / static_cast<T>(vector.x), y / static_cast<T>(vector.y));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator%(const T scalar) const {
  return Vec2<T>(x % scalar, y % scalar);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator%(const U scalar) const {
  return Vec2<T>(x % static_cast<T>(scalar), y % static_cast<T>(scalar));
}

template <typename T>
inline Vec2<T> Vec2<T>::operator%(const Vec2<T>& vector) const {
  return Vec2<T>(x % vector.x, y % vector.y);
}

template <typename T> template <typename U>
inline Vec2<T> Vec2<T>::operator%(const Vec2<U>& vector) const {
  return Vec2<T>(x % static_cast<T>(vector.x), y % static_cast<T>(vector.y));
}

template <typename T>
inline void Vec2<T>::operator=(const Vec2<T>& vector) {
  x = vector.x;
  y = vector.y;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator=(const Vec2<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
}

template <typename T>
inline void Vec2<T>::operator+=(const T scalar) {
  x += scalar;
  y += scalar;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator+=(const U scalar) {
  x += static_cast<T>(scalar);
  y += static_cast<T>(scalar);
}

template <typename T>
inline void Vec2<T>::operator+=(const Vec2<T>& vector) {
  x += vector.x;
  y += vector.y;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator+=(const Vec2<U>& vector) {
  x += static_cast<T>(vector.x);
  y += static_cast<T>(vector.y);
}

template <typename T>
inline void Vec2<T>::operator-=(const T scalar) {
  x -= scalar;
  y -= scalar;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator-=(const U scalar) {
  x -= static_cast<T>(scalar);
  y -= static_cast<T>(scalar);
}

template <typename T>
inline void Vec2<T>::operator-=(const Vec2<T>& vector) {
  x -= vector.x;
  y -= vector.y;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator-=(const Vec2<U>& vector) {
  x -= static_cast<T>(vector.x);
  y -= static_cast<T>(vector.y);
}

template <typename T>
inline void Vec2<T>::operator*=(const T scalar) {
  x *= scalar;
  y *= scalar;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator*=(const U scalar) {
  x *= static_cast<T>(scalar);
  y *= static_cast<T>(scalar);
}

template <typename T>
inline void Vec2<T>::operator*=(const Vec2<T>& vector) {
  x *= vector.x;
  y *= vector.y;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator*=(const Vec2<U>& vector) {
  x *= static_cast<T>(vector.x);
  y *= static_cast<T>(vector.y);
}

template <typename T>
inline void Vec2<T>::operator/=(const T scalar) {
  x /= scalar;
  y /= scalar;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator/=(const U scalar) {
  x /= static_cast<T>(scalar);
  y /= static_cast<T>(scalar);
}

template <typename T>
inline void Vec2<T>::operator/=(const Vec2<T>& vector) {
  x /= vector.x;
  y /= vector.y;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator/=(const Vec2<U>& vector) {
  x /= static_cast<T>(vector.x);
  y /= static_cast<T>(vector.y);
}

template <typename T>
inline void Vec2<T>::operator%=(const T scalar) {
  x %= scalar;
  y %= scalar;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator%=(const U scalar) {
  x %= static_cast<T>(scalar);
  y %= static_cast<T>(scalar);
}

template <typename T>
inline void Vec2<T>::operator%=(const Vec2<T>& vector) {
  x %= vector.x;
  y %= vector.y;
}

template <typename T> template <typename U>
inline void Vec2<T>::operator%=(const Vec2<U>& vector) {
  x %= static_cast<T>(vector.x);
  y %= static_cast<T>(vector.y);
}