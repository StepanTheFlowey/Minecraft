#pragma once
#include "vec2.hpp"

//Two component vector

template <typename T> Vec2<T>::Vec2() {
  x = 0;
  y = 0;
}

template <typename T> Vec2<T>::Vec2(T X, T Y) {
  x = X;
  y = Y;
}

template <typename T> template <typename U> Vec2<T>::Vec2(const Vec2<U>& vec) {
  x = static_cast<T>(vec.x);
  y = static_cast<T>(vec.y);
}

template <typename T> template <typename U> Vec2<T>::Vec2(const sf::Vector2<U>& vec) {
  x = static_cast<T>(vec.x);
  y = static_cast<T>(vec.y);
}

template <typename T> void Vec2<T>::print() const {
  std::cout << "X: " << x << " Y: " << y << std::endl;
}

template <typename T> void Vec2<T>::print(std::string str) const {
  std::cout << str << " X: " << x << " Y: " << y << std::endl;
}

template <typename T> void Vec2<T>::wprint() const {
  std::wcout << L"X: " << x << L" Y: " << y << std::endl;
}

template <typename T> void Vec2<T>::wprint(std::wstring str) const {
  std::wcout << str << L" X: " << x << L" Y: " << y << std::endl;
}

template <typename T> Vec2<T> Vec2<T>::operator+(const Vec2<T>& r) {
  return Vec2<T>(x + r.x, y + r.y);
}

template <typename T> template <typename U> Vec2<T> Vec2<T>::operator+(const  Vec2<U>& r) {
  return Vec2<T>(x + static_cast<T>(r.x), y + static_cast<T>(r.y));
}

template <typename T> Vec2<T> Vec2<T>::operator-(const Vec2<T>& r) {
  return Vec2<T>(x - r.x, y - r.y);
}

template <typename T> template <typename U> Vec2<T> Vec2<T>::operator-(const Vec2<U>& r) {
  return Vec2<T>(x - static_cast<T>(r.x), y - static_cast<T>(r.y));
}

template <typename T> Vec2<T> Vec2<T>::operator*(const T r) {
  return Vec2<T>(x * r, y * r);
}

template <typename T> Vec2<T> Vec2<T>::operator*(const Vec2<T>& r) {
  return Vec2<T>(x * r.x, y * r.y);
}

template <typename T> template <typename U> Vec2<T> Vec2<T>::operator*(const Vec2<U>& r) {
  return Vec2<T>(x * static_cast<T>(r.x), y * static_cast<T>(r.y));
}

template <typename T> Vec2<T> Vec2<T>::operator/(const T r) {
  return Vec2<T>(x / r, y / r);
}

template <typename T> Vec2<T> Vec2<T>::operator/(const Vec2<T>& r) {
  return Vec2<T>(x / r.x, y / r.y);
}

template <typename T> template <typename U> Vec2<T> Vec2<T>::operator/(const Vec2<U>& r) {
  return Vec2<T>(x / static_cast<T>(r.x), y / static_cast<T>(r.y));
}

template <typename T> Vec2<T> Vec2<T>::operator%(const T r) {
  return Vec2<T>(x % r, y % r);
}

template <typename T> Vec2<T> Vec2<T>::operator%(const Vec2<T>& r) {
  return Vec2<T>(x % r.x, y % r.y);
}

template <typename T> template <typename U> Vec2<T> Vec2<T>::operator%(const Vec2<U>& r) {
  return Vec2<T>(x % static_cast<T>(r.x), y % static_cast<T>(r.y));
}

template <typename T> void Vec2<T>::operator=(const Vec2<T>& r) {
  x = r.x;
  y = r.y;
}

template <typename T> template <typename U> void Vec2<T>::operator=(const Vec2<U>& r) {
  x = static_cast<T>(r.x);
  y = static_cast<T>(r.y);
}

template <typename T> void Vec2<T>::operator+=(const Vec2<T>& r) {
  x += r.x;
  y += r.y;
}

template <typename T> template <typename U> void Vec2<T>::operator+=(const Vec2<U>& r) {
  x += static_cast<T>(r.x);
  y += static_cast<T>(r.y);
}

template <typename T> void Vec2<T>::operator-=(const Vec2<T>& r) {
  x -= r.x;
  y -= r.y;
}

template <typename T> template <typename U> void Vec2<T>::operator-=(const Vec2<U>& r) {
  x -= static_cast<T>(r.x);
  y -= static_cast<T>(r.y);
}

template <typename T> void Vec2<T>::operator*=(const T r) {
  x *= r;
  y *= r;
}

template <typename T> void Vec2<T>::operator*=(const Vec2<T>& r) {
  x *= r.x;
  y *= r.y;
}

template <typename T> template <typename U> void Vec2<T>::operator*=(const Vec2<U>& r) {
  x *= static_cast<T>(r.x);
  y *= static_cast<T>(r.y);
}

template <typename T> void Vec2<T>::operator/=(const T r) {
  x /= r;
  y /= r;
}

template <typename T> void Vec2<T>::operator/=(const Vec2<T>& r) {
  x /= r.x;
  y /= r.y;
}

template <typename T> template <typename U> void Vec2<T>::operator/=(const Vec2<U>& r) {
  x /= static_cast<T>(r.x);
  y /= static_cast<T>(r.y);
}

template <typename T> void Vec2<T>::operator%=(const T r) {
  x %= r;
  y %= r;
}

template <typename T> void Vec2<T>::operator%=(const Vec2<T>& r) {
  x %= r.x;
  y %= r.y;
}

template <typename T> template <typename U> void Vec2<T>::operator%=(const Vec2<U>& r) {
  x %= static_cast<T>(r.x);
  y %= static_cast<T>(r.y);
}