#pragma once
#include "vec3.hpp"

template <typename T> Vec3<T>::Vec3() {
  x = 0;
  y = 0;
  z = 0;
}

template <typename T> Vec3<T>::Vec3(T X, T Y, T Z) {
  x = X;
  y = Y;
  z = Z;
}

template <typename T> Vec3<T>::~Vec3() {

}

template <typename T> template <typename U> Vec3<T>::Vec3(const Vec3<U>& vec) {
  x = static_cast<T>(vec.x);
  y = static_cast<T>(vec.y);
  z = static_cast<T>(vec.z);
}

template <typename T> template <typename U> Vec3<T>::Vec3(const sf::Vector3<U>& vec) {
  x = static_cast<T>(vec.x);
  y = static_cast<T>(vec.y);
  z = static_cast<T>(vec.z);
}

template <typename T> void Vec3<T>::print() const {
  std::cout << L"X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T> void Vec3<T>::print(std::string str) const {
  std::cout << str << L" X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T> void Vec3<T>::wprint() const {
  std::wcout << L"X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T> void Vec3<T>::wprint(std::wstring str) const {
  std::cout << str << L" X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T> Vec3<T> Vec3<T>::abs() {
  return Vec3<T>(std::abs(x), std::abs(y), std::abs(z));
}

template <typename T> double_t Vec3<T>::lenght() {
  return std::sqrt(x * x + y * y + z * z);
}

template <typename T> Vec3<T> Vec3<T>::normalize() {
  const T l = lenght();
  return Vec3<T>(x / l, y / l, z / l);
}

template <typename T> double_t Vec3<T>::distanceTo(Vec3<T> point) {
  T X = x - point.x;
  T Y = y - point.y;
  T Z = z - point.z;
  return std::sqrt(X * X + Y * Y + Z * Z);
}

template <typename T> inline void Vec3<T>::glVertex() {
  glVertex3d(static_cast<GLdouble>(x),
             static_cast<GLdouble>(y),
             static_cast<GLdouble>(z));
}

template <typename T> bool Vec3<T>::operator==(const Vec3<T>& r) {
  return x == r.x && y == r.y && z == r.z;
}

template <typename T> bool Vec3<T>::operator!=(const Vec3<T>& r) {
  return x != r.x || y != r.y || z != r.z;
}

template <typename T> Vec3<T> operator+(const Vec3<T>& r) {
  return Vec3<T>(x + r.x, y + r.y, z + r.z);
}

template <typename T, typename U> Vec3<T> Vec3<T>::operator+(const Vec3<U>& r) {
  return Vec3<T>(x + static_cast<T>(r.x), y + static_cast<T>(r.y), z + static_cast<T>(r.z));
}

template <typename T> Vec3<T> operator-(const Vec3<T>& r) {
  return Vec3<T>(x - r.x, y - r.y, z - r.z);
}

template <typename T, typename U> Vec3<T> operator-(const Vec3<U>& r) {
  return Vec3<T>(x - static_cast<T>(r.x), y - static_cast<T>(r.y), z - static_cast<T>(r.z));
}

template <typename T> Vec3<T> operator*(const T r) {
  return Vec3<T>(x * r, y * r, z * r);
}

template <typename T> Vec3<T> operator*(const Vec3<T>& r) {
  return Vec3<T>(x * r.x, y * r.y, z * r.z);
}

template <typename T, typename U> Vec3<T> operator*(const Vec3<U>& r) {
  return Vec3<T>(x * static_cast<T>(r.x), y * static_cast<T>(r.y), z * static_cast<T>(r.z));
}

template <typename T> Vec3<T> Vec3<T>::operator/(const T r) {
  return Vec3<T>(x / r, y / r, z / r);
}

template <typename T> Vec3<T> Vec3<T>::operator/(const Vec3<T>& r) {
  return Vec3<T>(x / r.x, y / r.y, z / r.z);
}

template <typename T, typename U> Vec3<T> Vec3<T>::operator/(const Vec3<U>& r) {
  return Vec3<T>(x / static_cast<T>(r.x), y / static_cast<T>(r.y), z / static_cast<T>(r.z));
}

template <typename T> Vec3<T> Vec3<T>::operator%(const T r) {
  return Vec3<T>(x % r, y % r, z % r);
}

template <typename T> Vec3<T> Vec3<T>::operator%(const Vec3<T>& r) {
  return Vec3<T>(x % r.x, y % r.y, z % r.z);
}

template <typename T, typename U> Vec3<T> Vec3<T>::operator%(const Vec3<U>& r) {
  return Vec3<T>(x % static_cast<T>(r.x), y % static_cast<T>(r.y), z % static_cast<T>(r.z));
}

template <typename T> void Vec3<T>::operator=(const Vec3<T>& r) {
  x = r.x;
  y = r.y;
  z = r.z;
}

template <typename T, typename U> void Vec3<T>::operator=(const Vec3<U>& r) {
  x = static_cast<T>(r.x);
  y = static_cast<T>(r.y);
  z = static_cast<T>(r.z);
}

template <typename T> void Vec3<T>::operator+=(const Vec3<T>& r) {
  x += r.x;
  y += r.y;
  z += r.z;
}

template <typename T, typename U> void Vec3<T>::operator+=(const Vec3<U>& r) {
  x += static_cast<T>(r.x);
  y += static_cast<T>(r.y);
  z += static_cast<T>(r.z);
}

template <typename T> void Vec3<T>::operator-=(const Vec3<T>& r) {
  x -= r.x;
  y -= r.y;
  z -= r.z;
}

template <typename T, typename U> void Vec3<T>::operator-=(const Vec3<U>& r) {
  x -= static_cast<T>(r.x);
  y -= static_cast<T>(r.y);
  z -= static_cast<T>(r.z);
}

template <typename T> void Vec3<T>::operator*=(const T r) {
  x *= r;
  y *= r;
  z *= r;
}

template <typename T> void Vec3<T>::operator*=(const Vec3<T>& r) {
  x *= r.x;
  y *= r.y;
  z *= r.z;
}

template <typename T, typename U> void Vec3<T>::operator*=(const Vec3<U>& r) {
  x *= static_cast<T>(r.x);
  y *= static_cast<T>(r.y);
  z *= static_cast<T>(r.z);
}

template <typename T> void Vec3<T>::operator/=(const T r) {
  x /= r;
  y /= r;
  z /= r;
}

template <typename T> void Vec3<T>::operator/=(const Vec3<T>& r) {
  x /= r.x;
  y /= r.y;
  z /= r.z;
}

template <typename T, typename U> void Vec3<T>::operator/=(const Vec3<U>& r) {
  x /= r.x;
  y /= r.y;
  z /= r.z;
}

template <typename T> void Vec3<T>::operator%=(const T r) {
  x %= r;
  y %= r;
  z %= r;
}

template <typename T> void Vec3<T>::operator%=(const Vec3<T>& r) {
  x %= r.x;
  y %= r.y;
  z %= r.z;
}

template <typename T, typename U> void Vec3<T>::operator%=(const Vec3<U>& r) {
  x %= r.x;
  y %= r.y;
  z %= r.z;
}