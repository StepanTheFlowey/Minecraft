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
  constexpr Vec2();

  //Component constructor
  constexpr Vec2(const T X, const T Y);

  //Copy constructor
  template <typename U>
  constexpr Vec2(const Vec2<U>& vector);

  //SFML different type compitablity constructor
  template <typename U>
  constexpr Vec2(const sf::Vector2<U>& vector);

  //Default destructor
  ~Vec2();

  //Prints vector components to std::cout
  inline void print() const;

  //Prints vector components to std::cout
  inline void print(std::string string) const;

  //Prints vector components to std::wcout
  inline void wprint() const;

  //Prints vector components to std::wcout
  inline void wprint(std::wstring string) const;

  //Returns absolute vector
  constexpr Vec2<T> abs() const;

  //Returns vector lenght
  constexpr double_t lenght() const;

  //Returns normalized vector
  constexpr Vec2<T> normalize() const;

  //Returns distance to another vector
  constexpr double_t distanceTo(Vec2<T> vector) const;

  //Calls glVertex2d(x, y)
  inline void glVertex() const;

  //Scalar add operator
  constexpr Vec2<T> operator+(const T scalar) const;

  //Different type scalar add operator
  template <typename U>
  constexpr Vec2<T> operator+(const U scalar) const;

  //Vector add operator
  constexpr Vec2<T> operator+(const Vec2<T>& vector) const;

  //Different type vector add operator
  template <typename U>
  constexpr Vec2<T> operator+(const Vec2<U>& vector) const;

  //Scalar substract operator
  constexpr Vec2<T> operator-(const T scalar) const;

  //Different type scalar substract operator
  template <typename U>
  constexpr Vec2<T> operator-(const U scalar) const;

  //Vector substract operator
  constexpr Vec2<T> operator-(const Vec2<T>& vector) const;

  //Different type vector substract operator
  template <typename U>
  constexpr Vec2<T> operator-(const Vec2<U>& vector) const;

  //Scalar multiply operator
  constexpr Vec2<T> operator*(const T scalar) const;

  //Different type scalar multiply operator
  template <typename U>
  constexpr Vec2<T> operator*(const U scalar) const;

  //Vector multiply operator
  constexpr Vec2<T> operator*(const Vec2<T>& vector) const;

  //Different type vector multiply operator
  template <typename U>
  constexpr Vec2<T> operator*(const Vec2<U>& vector) const;

  //Scalar divide operator
  constexpr Vec2<T> operator/(const T scalar) const;

  //Different type scalar divide operator
  template <typename U>
  constexpr Vec2<T> operator/(const U scalar) const;

  //Vector divide operator
  constexpr Vec2<T> operator/(const Vec2<T>& vector) const;

  //Different type vector divide operator
  template <typename U>
  constexpr Vec2<T> operator/(const Vec2<U>& vector) const;

  //Scalar modulo operator
  constexpr Vec2<T> operator%(const T scalar) const;

  //Different type scalar modulo operator
  template <typename U>
  constexpr Vec2<T> operator%(const U scalar) const;

  //Vector modulo operator
  constexpr Vec2<T> operator%(const Vec2<T>& vector) const;

  //Different type vector modulo operator
  template <typename U>
  constexpr Vec2<T> operator%(const Vec2<U>& vector) const;

  //Assignment operator
  constexpr void operator=(const Vec2<T>& vector);

  //Different type assignment operator
  template <typename U>
  constexpr void operator=(const Vec2<U>& vector);

  //Scalar assignment add operator
  constexpr void operator+=(const T scalar);

  //Different type scalar assignment add operator
  template <typename U>
  constexpr void operator+=(const U scalar);

  //Vector assignment add operator
  constexpr void operator+=(const Vec2<T>& vector);

  //Different type vector assignment add operator
  template <typename U>
  constexpr void operator+=(const Vec2<U>& vector);

  //Scalar assignment substract operator
  constexpr void operator-=(const T scalar);

  //Different type scalar assignment substract operator
  template <typename U>
  constexpr void operator-=(const U scalar);

  //Vector assignment substract operator
  constexpr void operator-=(const Vec2<T>& vector);

  //Different type vector assignment substract operator
  template <typename U>
  constexpr void operator-=(const Vec2<U>& vector);

  //Scalar assignment multiply operator
  constexpr void operator*=(const T scalar);

  //Different type scalar assignment multiply operator
  template <typename U>
  constexpr void operator*=(const U scalar);

  //Vector assignment multiply operator
  constexpr void operator*=(const Vec2<T>& vector);

  //Different type vector assignment multiply operator
  template <typename U>
  constexpr void operator*=(const Vec2<U>& vector);

  //Scalar assignment divide operator
  constexpr void operator/=(const T scalar);

  //Different type scalar assignment divide operator
  template <typename U>
  constexpr void operator/=(const U scalar);

  //Vector assignment divide operator
  constexpr void operator/=(const Vec2<T>& vector);

  //Different type vector assignment divide operator
  template <typename U>
  constexpr void operator/=(const Vec2<U>& vector);

  //Scaler assignment modulo operator
  constexpr void operator%=(const T scalar);

  //Different type scalar assignment modulo operator
  template <typename U>
  constexpr void operator%=(const U scalar);

  //Vector assignment modulo operator
  constexpr void operator%=(const Vec2<T>& vector);

  //Different type vector assignment modulo operator
  template <typename U>
  constexpr void operator%=(const Vec2<U>& vector);
};

#include "Vec2.inl"

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
