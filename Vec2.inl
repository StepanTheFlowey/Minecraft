#pragma once

#include <cmath>
#include <iostream>

template <typename T>
constexpr Vec2<T>::Vec2(const T _x, const T _y) :
  x(_x),
  y(_y) {

}

template <typename T> template <typename U>
constexpr Vec2<T>::Vec2(const Vec2<U>& vector) :
  x(static_cast<T>(vector.x)),
  y(static_cast<T>(vector.y)) {

}

template <typename T> template <typename U>
constexpr Vec2<T>::Vec2(const sf::Vector2<U>& vector) :
  x(static_cast<T>(vector.x)),
  y(static_cast<T>(vector.y)) {

}

template <typename T>
void Vec2<T>::print() const {
  std::cout << "X: " << x << " Y: " << y << std::endl;
}

template <typename T>
void Vec2<T>::print(const std::string& string) const {
  std::cout << string << " X: " << x << " Y: " << y << std::endl;
}

template <typename T>
void Vec2<T>::wprint() const {
  std::wcout << L"X: " << x << L" Y: " << y << std::endl;
}

template <typename T>
void Vec2<T>::wprint(const std::wstring& wstring) const {
  std::wcout << wstring << L" X: " << x << L" Y: " << y << std::endl;
}

template <typename T>
constexpr Vec2<T> Vec2<T>::abs() const {
  return Vec2<T>(std::abs(x), std::abs(y));
}

template <typename T>
constexpr double_t Vec2<T>::lenght() const {
  return std::sqrt(x * x + y * y);
}

template <typename T>
constexpr Vec2<T> Vec2<T>::normalize() const {
  const T l = lenght();
  return Vec2<T>(x / l, y / l);
}

template <typename T>
constexpr double_t Vec2<T>::distanceTo(const Vec2<T>& vector) const {
  T X = x - vector.x;
  T Y = y - vector.y;
  return std::sqrt(X * X + Y * Y);
}

template <typename T>
void Vec2<T>::glVertex() const {
  glVertex2d(
    static_cast<GLdouble>(x),
    static_cast<GLdouble>(y)
  );
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator+(const T scalar)const {
  return Vec2<T>(x + scalar, y + scalar);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator+(const U scalar) const {
  return Vec2<T>(x + static_cast<T>(scalar), y + static_cast<T>(scalar));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator+(const Vec2<T>& vector) const {
  return Vec2<T>(x + vector.x, y + vector.y);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator+(const  Vec2<U>& vector) const {
  return Vec2<T>(x + static_cast<T>(vector.x), y + static_cast<T>(vector.y));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator-(const T scalar)const {
  return Vec2<T>(x - scalar, y - scalar);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator-(const U scalar) const {
  return Vec2<T>(x - static_cast<T>(scalar), y - static_cast<T>(scalar));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator-(const Vec2<T>& vector) const {
  return Vec2<T>(x - vector.x, y - vector.y);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator-(const Vec2<U>& vector) const {
  return Vec2<T>(x - static_cast<T>(vector.x), y - static_cast<T>(vector.y));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator*(const T scalar) const {
  return Vec2<T>(x * scalar, y * scalar);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator*(const U scalar) const {
  return Vec2<T>(x * static_cast<T>(scalar), y * static_cast<T>(scalar));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator*(const Vec2<T>& vector) const {
  return Vec2<T>(x * vector.x, y * vector.y);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator*(const Vec2<U>& vector) const {
  return Vec2<T>(x * static_cast<T>(vector.x), y * static_cast<T>(vector.y));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator/(const T scalar) const {
  return Vec2<T>(x / scalar, y / scalar);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator/(const U scalar) const {
  return Vec2<T>(x / static_cast<T>(scalar), y / static_cast<T>(scalar));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator/(const Vec2<T>& vector) const {
  return Vec2<T>(x / vector.x, y / vector.y);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator/(const Vec2<U>& vector) const {
  return Vec2<T>(x / static_cast<T>(vector.x), y / static_cast<T>(vector.y));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator%(const T scalar) const {
  return Vec2<T>(x % scalar, y % scalar);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator%(const U scalar) const {
  return Vec2<T>(x % static_cast<T>(scalar), y % static_cast<T>(scalar));
}

template <typename T>
constexpr Vec2<T> Vec2<T>::operator%(const Vec2<T>& vector) const {
  return Vec2<T>(x % vector.x, y % vector.y);
}

template <typename T> template <typename U>
constexpr Vec2<T> Vec2<T>::operator%(const Vec2<U>& vector) const {
  return Vec2<T>(x % static_cast<T>(vector.x), y % static_cast<T>(vector.y));
}

template <typename T>
constexpr void Vec2<T>::operator=(const Vec2<T>& vector) {
  x = vector.x;
  y = vector.y;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator=(const Vec2<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
}

template <typename T>
constexpr void Vec2<T>::operator+=(const T scalar) {
  x += scalar;
  y += scalar;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator+=(const U scalar) {
  x += static_cast<T>(scalar);
  y += static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec2<T>::operator+=(const Vec2<T>& vector) {
  x += vector.x;
  y += vector.y;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator+=(const Vec2<U>& vector) {
  x += static_cast<T>(vector.x);
  y += static_cast<T>(vector.y);
}

template <typename T>
constexpr void Vec2<T>::operator-=(const T scalar) {
  x -= scalar;
  y -= scalar;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator-=(const U scalar) {
  x -= static_cast<T>(scalar);
  y -= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec2<T>::operator-=(const Vec2<T>& vector) {
  x -= vector.x;
  y -= vector.y;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator-=(const Vec2<U>& vector) {
  x -= static_cast<T>(vector.x);
  y -= static_cast<T>(vector.y);
}

template <typename T>
constexpr void Vec2<T>::operator*=(const T scalar) {
  x *= scalar;
  y *= scalar;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator*=(const U scalar) {
  x *= static_cast<T>(scalar);
  y *= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec2<T>::operator*=(const Vec2<T>& vector) {
  x *= vector.x;
  y *= vector.y;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator*=(const Vec2<U>& vector) {
  x *= static_cast<T>(vector.x);
  y *= static_cast<T>(vector.y);
}

template <typename T>
constexpr void Vec2<T>::operator/=(const T scalar) {
  x /= scalar;
  y /= scalar;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator/=(const U scalar) {
  x /= static_cast<T>(scalar);
  y /= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec2<T>::operator/=(const Vec2<T>& vector) {
  x /= vector.x;
  y /= vector.y;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator/=(const Vec2<U>& vector) {
  x /= static_cast<T>(vector.x);
  y /= static_cast<T>(vector.y);
}

template <typename T>
constexpr void Vec2<T>::operator%=(const T scalar) {
  x %= scalar;
  y %= scalar;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator%=(const U scalar) {
  x %= static_cast<T>(scalar);
  y %= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec2<T>::operator%=(const Vec2<T>& vector) {
  x %= vector.x;
  y %= vector.y;
}

template <typename T> template <typename U>
constexpr void Vec2<T>::operator%=(const Vec2<U>& vector) {
  x %= static_cast<T>(vector.x);
  y %= static_cast<T>(vector.y);
}
