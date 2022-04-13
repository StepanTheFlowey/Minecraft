#pragma once

#include "glad.h"
#include <string>
#include <SFML/System/Vector2.hpp>

//Two component vector
template <typename T> class Vec2 {
public:
  T x;
  T y;

  //Default constructor
  Vec2();

  //Component constructor
  Vec2(T X, T Y);

  //Copy constrcutor
  explicit Vec2(const Vec2<T>& vector);

  //Different type copy constructor
  template <typename U>
  Vec2(const Vec2<U>& vector);

  //SFML compitaability constructor
  explicit Vec2(const sf::Vector2<T>& vector);

  //SFML different type compitablity constructor
  template <typename U>
  Vec2(const sf::Vector2<U>& vector);

  //Prints vector components
  void print() const;

  //Prints string and vector component
  void print(std::string string) const;

  //Prints vector component
  void wprint() const;

  //Prints string and vector component
  void wprint(std::wstring string) const;

  //Returns absolute vector
  Vec2<T> abs() const;

  //Returns vector lenght
  double_t lenght() const;

  //Returns normalized vector
  Vec2<T> normalize() const;

  //Returns distance to another vector
  double_t distanceTo(Vec2<T> vector) const;

  //Calls glVertex2d(x, y)
  void glVertex() const;

  //Scalar add operator
  Vec2<T> operator+(const T scalar) const;

  //Different type scalar add operator
  template <typename U>
  Vec2<T> operator+(const U scalar) const;

  //Vector add operator
  Vec2<T> operator+(const Vec2<T>& vector) const;

  //Different type vector add operator
  template <typename U>
  Vec2<T> operator+(const Vec2<U>& vector) const;

  //Scalar substract operator
  Vec2<T> operator-(const T scalar) const;

  //Different type scalar substract operator
  template <typename U>
  Vec2<T> operator-(const U scalar) const;

  //Vector substract operator
  Vec2<T> operator-(const Vec2<T>& vector) const;

  //Different type vector substract operator
  template <typename U>
  Vec2<T> operator-(const Vec2<U>& vector) const;

  //Scalar multiply operator
  Vec2<T> operator*(const T scalar) const;

  //Different type scalar multiply operator
  template <typename U>
  Vec2<T> operator*(const U scalar) const;

  //Vector multiply operator
  Vec2<T> operator*(const Vec2<T>& vector) const;

  //Different type vector multiply operator
  template <typename U>
  Vec2<T> operator*(const Vec2<U>& vector) const;

  //Scalar divide operator
  Vec2<T> operator/(const T scalar) const;

  //Different type scalar divide operator
  template <typename U>
  Vec2<T> operator/(const U scalar) const;

  //Vector divide operator
  Vec2<T> operator/(const Vec2<T>& vector) const;

  //Different type vector divide operator
  template <typename U>
  Vec2<T> operator/(const Vec2<U>& vector) const;

  //Scalar modulo operator
  Vec2<T> operator%(const T scalar) const;

  //Different type scalar modulo operator
  template <typename U>
  Vec2<T> operator%(const U scalar) const;

  //Vector modulo operator
  Vec2<T> operator%(const Vec2<T>& vector) const;

  //Different type vector modulo operator
  template <typename U>
  Vec2<T> operator%(const Vec2<U>& vector) const;

  //Assignment operator
  void operator=(const Vec2<T>& vector);

  //Different type assignment operator
  template <typename U>
  void operator=(const Vec2<U>& vector);

  //Scalar assignment add operator
  void operator+=(const T scalar);

  //Different type scalar assignment add operator
  template <typename U>
  void operator+=(const U scalar);

  //Vector assignment add operator
  void operator+=(const Vec2<T>& vector);

  //Different type vector assignment add operator
  template <typename U>
  void operator+=(const Vec2<U>& vector);

  //Scalar assignment substract operator
  void operator-=(const T scalar);

  //Different type scalar assignment substract operator
  template <typename U>
  void operator-=(const U scalar);

  //Vector assignment substract operator
  void operator-=(const Vec2<T>& vector);

  //Different type vector assignment substract operator
  template <typename U>
  void operator-=(const Vec2<U>& vector);

  //Scalar assignment multiply operator
  void operator*=(const T scalar);

  //Different type scalar assignment multiply operator
  template <typename U>
  void operator*=(const U scalar);

  //Vector assignment multiply operator
  void operator*=(const Vec2<T>& vector);

  //Different type vector assignment multiply operator
  template <typename U>
  void operator*=(const Vec2<U>& vector);
  
  //Scalar assignment divide operator
  void operator/=(const T scalar);
  
  //Different type scalar assignment divide operator
  template <typename U>
  void operator/=(const U scalar);
  
  //Vector assignment divide operator
  void operator/=(const Vec2<T>& vector);
  
  //Different type vector assignment divide operator
  template <typename U>
  void operator/=(const Vec2<U>& vector);

  //Scaler assignment modulo operator
  void operator%=(const T scalar);

  //Different type scalar assignment modulo operator
  template <typename U>
  void operator%=(const U scalar);

  //Vector assignment modulo operator
  void operator%=(const Vec2<T>& vector);

  //Different type vector assignment modulo operator
  template <typename U>
  void operator%=(const Vec2<U>& vector);
};

#include "vec2.inl"

using Vec2i = Vec2<int>;
using Vec2i8 = Vec2<int8_t>;
using Vec2i16 = Vec2<int16_t>;
using Vec2i32 = Vec2<int32_t>;
using Vec2i64 = Vec2<int64_t>;

using Vec2u = Vec2<unsigned>;
using Vec2u8 = Vec2<uint8_t>;
using Vec2u16 = Vec2<uint16_t>;
using Vec2u32 = Vec2<uint32_t>;
using Vec2u64 = Vec2<uint64_t>;

using Vec2f = Vec2<float_t>;
using Vec2d = Vec2<double_t>;
