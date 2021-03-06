#pragma once

#include "Vec2.hpp"
#include <SFML/System/Vector3.hpp>

//Three component vector
template <typename T>
class Vec3 {
public:

  T x = 0;
  T y = 0;
  T z = 0;

  //Default constructor
  constexpr Vec3() = default;

  //Component constructor
  constexpr Vec3(const T x, const T y, const T z);

  //Copy constrcutor
  template <typename U>
  constexpr Vec3(const Vec3<U>& vector);

  //SFML compitablity constructor
  template <typename U>
  constexpr Vec3(const sf::Vector3<U>& vector);

  //Default destructor
  ~Vec3() = default;

  //Prints vector components to std::cout
  void print() const;

  //Prints vector components to std::cout
  void print(const std::string& str) const;

  //Prints vector components to std::wcout
  void wprint() const;

  //Prints vector components to std::wcout
  void wprint(const std::wstring& wstr) const;

  //Absolute vector
  constexpr Vec3<T> abs() const;

  //Scalar lenght of vector
  constexpr double_t lenght() const;

  //Normalizing vector
  constexpr Vec3<T> normalize() const;

  //Distance to other vector
  constexpr double_t distanceTo(const Vec3<T> vector) const;

  //
  constexpr T dotProduct(const Vec3<T> vector) const;

  //
  constexpr Vec3<T> vectorProduct(const Vec3<T> vector) const;

  //Call glVertex3(x,y,z)
  void glVertex() const;

  //Returns vector with x = 0
  constexpr Vec3<T> nullX() const;

  //Returns vector with y = 0
  constexpr Vec3<T> nullY() const;

  //Returns vector with z = 0
  constexpr Vec3<T> nullZ() const;

  //Returns vector without x
  constexpr Vec2<T> cutX() const;

  //Returns vector without y
  constexpr Vec2<T> cutY() const;

  //Returns vector without z
  constexpr Vec2<T> cutZ() const;

  //
  constexpr bool operator==(const Vec3<T> vector) const;

  //
  constexpr bool operator!=(const Vec3<T> vector) const;

  //TODO: Description
  constexpr Vec3<T> operator+(const T) const;

  //
  template <typename U>
  constexpr Vec3<T> operator+(const U) const;

  //
  constexpr Vec3<T> operator+(const Vec3<T>&) const;

  //
  template <typename U>
  constexpr Vec3<T> operator+(const Vec3<U>&) const;

  //
  constexpr Vec3<T> operator-(const T) const;

  //
  template <typename U>
  constexpr Vec3<T> operator-(const U) const;

  //
  constexpr Vec3<T> operator-(const Vec3<T>&) const;

  //
  template <typename U>
  constexpr Vec3<T> operator-(const Vec3<U>&) const;

  //
  constexpr Vec3<T> operator*(const T) const;

  //
  template <typename U>
  constexpr Vec3<T> operator*(const U) const;

  //
  constexpr Vec3<T> operator*(const Vec3<T>&) const;

  //
  template <typename U>
  constexpr Vec3<T> operator*(const Vec3<U>&) const;

  //
  constexpr Vec3<T> operator/(const T) const;

  //
  template <typename U>
  constexpr Vec3<T> operator/(const U) const;

  //
  constexpr Vec3<T> operator/(const Vec3<T>&) const;

  //
  template <typename U>
  constexpr Vec3<T> operator/(const Vec3<U>&) const;

  //
  constexpr Vec3<T> operator%(const T) const;

  //
  template <typename U>
  constexpr Vec3<T> operator%(const U) const;

  //
  constexpr Vec3<T> operator%(const Vec3<T>&) const;

  //
  template <typename U>
  constexpr Vec3<T> operator%(const Vec3<U>&) const;

  //
  constexpr void operator=(const Vec3<T>&);

  //
  template <typename U>
  constexpr void operator=(const Vec3<U>&);

  //
  constexpr void operator+=(const T);

  //
  template <typename U>
  constexpr void operator+=(const U);

  //
  constexpr void operator+=(const Vec3<T>&);

  //
  template<typename U>
  constexpr void operator+=(const Vec3<U>&);

  //
  constexpr void operator-=(const T);

  //
  template <typename U>
  constexpr void operator-=(const U);

  //
  constexpr void operator-=(const Vec3<T>&);

  //
  template<typename U>
  constexpr void operator-=(const Vec3<U>&);

  //
  constexpr void operator*=(const T);

  //
  template<typename U>
  constexpr void operator*=(const U);

  //
  constexpr void operator*=(const Vec3<T>&);

  //
  template<typename U>
  constexpr void operator*=(const Vec3<U>&);

  //
  constexpr void operator/=(const T);

  //
  template<typename U>
  constexpr void operator/=(const U);

  //
  constexpr void operator/=(const Vec3<T>&);

  //
  template<typename U>
  constexpr void operator/=(const Vec3<U>&);

  //
  constexpr void operator%=(const T);

  //
  template<typename U>
  constexpr void operator%=(const U);

  //
  constexpr void operator%=(const Vec3<T>&);

  //
  template<typename U>
  constexpr void operator%=(const Vec3<U>&);
};

#include "Vec3.inl"

using Vec3i = Vec3<int>;
using Vec3i8 = Vec3<int8_t>;
using Vec3i16 = Vec3<int16_t>;
using Vec3i32 = Vec3<int32_t>;
using Vec3i64 = Vec3<int64_t>;

using Vec3u = Vec3<unsigned>;
using Vec3u8 = Vec3<uint8_t>;
using Vec3u16 = Vec3<uint16_t>;
using Vec3u32 = Vec3<uint32_t>;
using Vec3u64 = Vec3<uint64_t>;

using Vec3f = Vec3<float_t>;
using Vec3d = Vec3<double_t>;
