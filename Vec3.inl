#pragma once

#include "Vec3.hpp"

template <typename T>
constexpr Vec3<T>::Vec3(const T _x, const T _y, const T _z) :
  x(_x),
  y(_y),
  z(_z) {

}

template <typename T> template <typename U>
constexpr Vec3<T>::Vec3(const Vec3<U>& vector) :
  x(static_cast<T>(vector.x)),
  y(static_cast<T>(vector.y)),
  z(static_cast<T>(vector.z)) {

}

template <typename T> template <typename U>
constexpr Vec3<T>::Vec3(const sf::Vector3<U>& vector) :
  x(static_cast<T>(vector.x)),
  y(static_cast<T>(vector.y)),
  z(static_cast<T>(vector.z)) {

}

template <typename T>
void Vec3<T>::print() const {
  std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
}

template <typename T>
void Vec3<T>::print(const std::string& string) const {
  std::cout << string << " X: " << x << " Y: " << y << " Z: " << z << std::endl;
}

template <typename T>
void Vec3<T>::wprint() const {
  std::wcout << L"X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T>
void Vec3<T>::wprint(const std::wstring& wstring) const {
  std::wcout << wstring << L" X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T>
constexpr Vec3<T> Vec3<T>::abs() const {
  return Vec3<T>(std::abs(x), std::abs(y), std::abs(z));
}

template <typename T>
constexpr double_t Vec3<T>::lenght() const {
  return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
constexpr Vec3<T> Vec3<T>::normalize() const {
  const T l = lenght();
  return Vec3<T>(x / l, y / l, z / l);
}

template <typename T>
constexpr double_t Vec3<T>::distanceTo(const Vec3<T> vector) const {
  T X = x - vector.x;
  T Y = y - vector.y;
  T Z = z - vector.z;
  return std::sqrt(X * X + Y * Y + Z * Z);
}

template<typename T>
constexpr T Vec3<T>::dotProduct(const Vec3<T> vector) const {
  return x * vector.x + y * vector.y + z * vector.z;
}

template<typename T>
constexpr Vec3<T> Vec3<T>::vectorProduct(const Vec3<T> vector) const {
  return Vec3<T>(y * vector.z - z * vector.y,
                 z * vector.x - x * vector.z,
                 x * vector.y - y * vector.x);
}

template <typename T>
void Vec3<T>::glVertex() const {
  glVertex3d(
    static_cast<GLdouble>(x),
    static_cast<GLdouble>(y),
    static_cast<GLdouble>(z)
  );
}

template <typename T>
constexpr Vec3<T> Vec3<T>::nullX() const {
  return Vec3<T>(0, y, z);
}

template <typename T>
constexpr Vec3<T> Vec3<T>::nullY() const {
  return Vec3<T>(x, 0, z);
}

template <typename T>
constexpr Vec3<T> Vec3<T>::nullZ() const {
  return Vec3<T>(x, y, 0);
}

template <typename T>
constexpr Vec2<T> Vec3<T>::cutX() const {
  return Vec2<T>(y, z);
}

template <typename T>
constexpr Vec2<T> Vec3<T>::cutY() const {
  return Vec2<T>(x, z);
}

template <typename T>
constexpr Vec2<T> Vec3<T>::cutZ() const {
  return Vec2<T>(x, y);
}

template <typename T>
constexpr bool Vec3<T>::operator==(const Vec3<T> vector) const {
  return x == vector.x && y == vector.y && z == vector.z;
}

template <typename T>
constexpr bool Vec3<T>::operator!=(const Vec3<T> vector) const {
  return x != vector.x && y != vector.y && z != vector.z;
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator+(const T scalar)const {
  return Vec3<T>(x + scalar, y + scalar, z + scalar);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator+(const U scalar) const {
  return Vec3<T>(x + static_cast<T>(scalar), y + static_cast<T>(scalar), z + static_cast<T>(scalar));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator+(const Vec3<T>& vector) const {
  return Vec3<T>(x + vector.x, y + vector.y, z + vector.z);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator+(const Vec3<U>& vector) const {
  return Vec3<T>(x + static_cast<T>(vector.x), y + static_cast<T>(vector.y), z + static_cast<T>(vector.z));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator-(const T scalar) const {
  return Vec3<T>(x - scalar, y - scalar, z - scalar);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator-(const U scalar) const {
  return Vec3<T>(x - static_cast<T>(scalar), y - static_cast<T>(scalar), z - static_cast<T>(scalar));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator-(const Vec3<T>& vector) const {
  return Vec3<T>(x - vector.x, y - vector.y, z - vector.z);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator-(const Vec3<U>& vector) const {
  return Vec3<T>(x - static_cast<T>(vector.x), y - static_cast<T>(vector.y), z - static_cast<T>(vector.z));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator*(const T scalar) const {
  return Vec3<T>(x * scalar, y * scalar, z * scalar);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator*(const U scalar) const {
  return Vec3<T>(x * static_cast<T>(scalar), y * static_cast<T>(scalar), z * static_cast<T>(scalar));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator*(const Vec3<T>& vector) const {
  return Vec3<T>(x * vector.x, y * vector.y, z * vector.z);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator*(const Vec3<U>& vector) const {
  return Vec3<T>(x * static_cast<T>(vector.x), y * static_cast<T>(vector.y), z * static_cast<T>(vector.z));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator/(const T scalar) const {
  return Vec3<T>(x / scalar, y / scalar, z / scalar);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator/(const U scalar) const {
  return Vec3<T>(x / static_cast<T>(scalar), y / static_cast<T>(scalar), z / static_cast<T>(scalar));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator/(const Vec3<T>& vector) const {
  return Vec3<T>(x / vector.x, y / vector.y, z / vector.z);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator/(const Vec3<U>& vector) const {
  return Vec3<T>(x / static_cast<T>(vector.x), y / static_cast<T>(vector.y), z / static_cast<T>(vector.z));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator%(const T scalar) const {
  return Vec3<T>(x % scalar, y % scalar, z % scalar);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator%(const U scalar) const {
  return Vec3<T>(x % static_cast<T>(scalar), y % static_cast<T>(scalar), z % static_cast<T>(scalar));
}

template <typename T>
constexpr Vec3<T> Vec3<T>::operator%(const Vec3<T>& vector) const {
  return Vec3<T>(x % vector.x, y % vector.y, z % vector.z);
}

template <typename T> template <typename U>
constexpr Vec3<T> Vec3<T>::operator%(const Vec3<U>& vector) const {
  return Vec3<T>(x % static_cast<T>(vector.x), y % static_cast<T>(vector.y), z % static_cast<T>(vector.z));
}

template <typename T>
constexpr void Vec3<T>::operator=(const Vec3<T>& vector) {
  x = vector.x;
  y = vector.y;
  z = vector.z;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator=(const Vec3<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
  z = static_cast<T>(vector.z);
}

template <typename T>
constexpr void Vec3<T>::operator+=(const T scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator+=(const U scalar) {
  x += static_cast<T>(scalar);
  y += static_cast<T>(scalar);
  z += static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec3<T>::operator+=(const Vec3<T>& vector) {
  x += vector.x;
  y += vector.y;
  z += vector.z;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator+=(const Vec3<U>& vector) {
  x += static_cast<T>(vector.x);
  y += static_cast<T>(vector.y);
  z += static_cast<T>(vector.z);
}

template <typename T>
constexpr void Vec3<T>::operator-=(const T scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator-=(const U scalar) {
  x -= static_cast<T>(scalar);
  y -= static_cast<T>(scalar);
  z -= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec3<T>::operator-=(const Vec3<T>& vector) {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator-=(const Vec3<U>& vector) {
  x -= static_cast<T>(vector.x);
  y -= static_cast<T>(vector.y);
  z -= static_cast<T>(vector.z);
}

template <typename T>
constexpr void Vec3<T>::operator*=(const T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator*=(const U scalar) {
  x *= static_cast<T>(scalar);
  y *= static_cast<T>(scalar);
  z *= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec3<T>::operator*=(const Vec3<T>& vector) {
  x *= vector.x;
  y *= vector.y;
  z *= vector.z;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator*=(const Vec3<U>& vector) {
  x *= static_cast<T>(vector.x);
  y *= static_cast<T>(vector.y);
  z *= static_cast<T>(vector.z);
}

template <typename T>
constexpr void Vec3<T>::operator/=(const T scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator/=(const U scalar) {
  x /= static_cast<T>(scalar);
  y /= static_cast<T>(scalar);
  z /= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec3<T>::operator/=(const Vec3<T>& vector) {
  x /= vector.x;
  y /= vector.y;
  z /= vector.z;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator/=(const Vec3<U>& vector) {
  x /= static_cast<T>(vector.x);
  y /= static_cast<T>(vector.y);
  z /= static_cast<T>(vector.z);
}

template <typename T>
constexpr void Vec3<T>::operator%=(const T scalar) {
  x %= scalar;
  y %= scalar;
  z %= scalar;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator%=(const U scalar) {
  x %= static_cast<T>(scalar);
  y %= static_cast<T>(scalar);
  z %= static_cast<T>(scalar);
}

template <typename T>
constexpr void Vec3<T>::operator%=(const Vec3<T>& vector) {
  x %= vector.x;
  y %= vector.y;
  z %= vector.z;
}

template <typename T> template <typename U>
constexpr void Vec3<T>::operator%=(const Vec3<U>& vector) {
  x %= static_cast<T>(vector.x);
  y %= static_cast<T>(vector.y);
  z %= static_cast<T>(vector.z);
}
