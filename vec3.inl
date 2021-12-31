#pragma once

template <typename T>
inline Vec3<T>::Vec3() {
  x = 0;
  y = 0;
  z = 0;
}

template <typename T>
inline Vec3<T>::Vec3(T X, T Y, T Z) {
  x = X;
  y = Y;
  z = Z;
}

template <typename T> template <typename U>
inline Vec3<T>::Vec3(const Vec3<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
  z = static_cast<T>(vector.z);
}

template <typename T> template <typename U>
inline Vec3<T>::Vec3(const sf::Vector3<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
  z = static_cast<T>(vector.z);
}

template <typename T>
inline void Vec3<T>::print() const {
  std::cout << L"X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T>
inline void Vec3<T>::print(std::string str) const {
  std::cout << str << L" X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T>
inline void Vec3<T>::wprint() const {
  std::wcout << L"X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T>
inline void Vec3<T>::wprint(std::wstring str) const {
  std::wcout << str << L" X: " << x << L" Y: " << y << L" Z: " << z << std::endl;
}

template <typename T>
inline Vec3<T> Vec3<T>::abs() const {
  return Vec3<T>(std::abs(x), std::abs(y), std::abs(z));
}

template <typename T>
inline double_t Vec3<T>::lenght() const {
  return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
inline Vec3<T> Vec3<T>::normalize() const {
  const T l = lenght();
  return Vec3<T>(x / l, y / l, z / l);
}

template <typename T>
inline double_t Vec3<T>::distanceTo(Vec3<T> vector) const {
  T X = x - vector.x;
  T Y = y - vector.y;
  T Z = z - vector.z;
  return std::sqrt(X * X + Y * Y + Z * Z);
}

template <typename T>
inline void Vec3<T>::glVertex() const {
  glVertex3d(
    static_cast<GLdouble>(x),
    static_cast<GLdouble>(y),
    static_cast<GLdouble>(z)
  );
}

template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T>& vector) const {
  return x == vector.x && y == vector.y && z == vector.z;
}

template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T>& vector) const {
  return x != vector.x || y != vector.y || z != vector.z;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator+(const T scalar)const {
  return Vec3<T>(x + scalar, y + scalar, z + scalar);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator+(const U scalar) const {
  return Vec3<T>(x + static_cast<T>(scalar), y + static_cast<T>(scalar), z + static_cast<T>(scalar));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3<T>& vector) const {
  return Vec3<T>(x + vector.x, y + vector.y, z + vector.z);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator+(const Vec3<U>& vector) const {
  return Vec3<T>(x + static_cast<T>(vector.x), y + static_cast<T>(vector.y), z + static_cast<T>(vector.z));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator-(const T scalar)const {
  return Vec3<T>(x - scalar, y - scalar, z - scalar);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator-(const U scalar) const {
  return Vec3<T>(x - static_cast<T>(scalar), y - static_cast<T>(scalar), z - static_cast<T>(scalar));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3<T>& vector) const {
  return Vec3<T>(x - vector.x, y - vector.y, z - vector.z);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator-(const Vec3<U>& vector) const {
  return Vec3<T>(x - static_cast<T>(vector.x), y - static_cast<T>(vector.y), z - static_cast<T>(vector.z));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator*(const T scalar) const {
  return Vec3<T>(x * scalar, y * scalar, z * scalar);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator*(const U scalar) const {
  return Vec3<T>(x * static_cast<T>(scalar), y * static_cast<T>(scalar), z * static_cast<T>(scalar));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator*(const Vec3<T>& vector) const {
  return Vec3<T>(x * vector.x, y * vector.y, z * vector.z);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator*(const Vec3<U>& vector) const {
  return Vec3<T>(x * static_cast<T>(vector.x), y * static_cast<T>(vector.y), z * static_cast<T>(vector.z));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator/(const T scalar) const {
  return Vec3<T>(x / scalar, y / scalar, z / scalar);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator/(const U scalar) const {
  return Vec3<T>(x / static_cast<T>(scalar), y / static_cast<T>(scalar), z / static_cast<T>(scalar));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator/(const Vec3<T>& vector) const {
  return Vec3<T>(x / vector.x, y / vector.y, z / vector.z);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator/(const Vec3<U>& vector) const {
  return Vec3<T>(x / static_cast<T>(vector.x), y / static_cast<T>(vector.y), z / static_cast<T>(vector.z));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator%(const T scalar) const {
  return Vec3<T>(x % scalar, y % scalar, z % scalar);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator%(const U scalar) const {
  return Vec3<T>(x % static_cast<T>(scalar), y % static_cast<T>(scalar), z % static_cast<T>(scalar));
}

template <typename T>
inline Vec3<T> Vec3<T>::operator%(const Vec3<T>& vector) const {
  return Vec3<T>(x % vector.x, y % vector.y, z % vector.z);
}

template <typename T> template <typename U>
inline Vec3<T> Vec3<T>::operator%(const Vec3<U>& vector) const {
  return Vec3<T>(x % static_cast<T>(vector.x), y % static_cast<T>(vector.y), z % static_cast<T>(vector.z));
}

template <typename T>
inline void Vec3<T>::operator=(const Vec3<T>& vector) {
  x = vector.x;
  y = vector.y;
  z = vector.z;
}

template <typename T> template <typename U>
inline void Vec3<T>::operator=(const Vec3<U>& vector) {
  x = static_cast<T>(vector.x);
  y = static_cast<T>(vector.y);
  z = static_cast<T>(vector.z);
}

template <typename T>
inline void Vec3<T>::operator+=(const Vec3<T>& vector) {
  x += vector.x;
  y += vector.y;
  z += vector.z;
}

template <typename T> template <typename U>
inline void Vec3<T>::operator+=(const Vec3<U>& vector) {
  x += static_cast<T>(vector.x);
  y += static_cast<T>(vector.y);
  z += static_cast<T>(vector.z);
}

template <typename T>
inline void Vec3<T>::operator-=(const Vec3<T>& vector) {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
}

template <typename T> template <typename U>
inline void Vec3<T>::operator-=(const Vec3<U>& vector) {
  x -= static_cast<T>(vector.x);
  y -= static_cast<T>(vector.y);
  z -= static_cast<T>(vector.z);
}

template <typename T>
inline void Vec3<T>::operator*=(const T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

template <typename T>
inline void Vec3<T>::operator*=(const Vec3<T>& vector) {
  x *= vector.x;
  y *= vector.y;
  z *= vector.z;
}

template <typename T> template <typename U>
inline void Vec3<T>::operator*=(const Vec3<U>& vector) {
  x *= static_cast<T>(vector.x);
  y *= static_cast<T>(vector.y);
  z *= static_cast<T>(vector.z);
}

template <typename T>
inline void Vec3<T>::operator/=(const T scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

template <typename T>
inline void Vec3<T>::operator/=(const Vec3<T>& vector) {
  x /= vector.x;
  y /= vector.y;
  z /= vector.z;
}

template <typename T> template <typename U>
inline void Vec3<T>::operator/=(const Vec3<U>& vector) {
  x /= vector.x;
  y /= vector.y;
  z /= vector.z;
}

template <typename T>
inline void Vec3<T>::operator%=(const T scalar) {
  x %= scalar;
  y %= scalar;
  z %= scalar;
}

template <typename T>
inline void Vec3<T>::operator%=(const Vec3<T>& vector) {
  x %= vector.x;
  y %= vector.y;
  z %= vector.z;
}

template <typename T> template <typename U>
inline void Vec3<T>::operator%=(const Vec3<U>& vector) {
  x %= vector.x;
  y %= vector.y;
  z %= vector.z;
}