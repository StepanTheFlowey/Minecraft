#pragma once

#include "Vec2.hpp"
#include <SFML/System/Vector3.hpp>

//Three component vector
template <typename T> class Vec3 {
public:

  T x;
  T y;
  T z;

  //Default constructor
  constexpr Vec3();

  //Component constructor
  constexpr Vec3(const T X, const T Y, const T Z);

  //Copy constrcutor
  template <typename U>
  constexpr Vec3(const Vec3<U>& vector);

  //SFML different type compitablity constructor
  template <typename U>
  constexpr Vec3(const sf::Vector3<U>& vector);

  //Default destructor
  ~Vec3();

  //Prints vector components to std::cout
  void print() const;

  //Prints vector components to std::cout
  void print(const std::string str) const;

  //Prints vector components to std::wcout
  void wprint() const;

  //Prints vector components to std::wcout
  void wprint(const std::wstring wstr) const;

  //Absolute vector
  Vec3<T> abs() const;

  //Scalar lenght of vector
  double_t lenght() const;

  //Normalizing vector
  Vec3<T> normalize() const;

  //Distance to other vector
  double_t distanceTo(const Vec3<T> vector) const;

  //
  T dotProduct(const Vec3<T> vector) const;

  //
  Vec3<T> vectorProduct(const Vec3<T> vector) const;

  //Call glVertex3(x,y,z)
  void glVertex() const;

  //Returns vector with x = 0
  Vec3<T> nullX() const;

  //Returns vector with y = 0
  Vec3<T> nullY() const;

  //Returns vector with z = 0
  Vec3<T> nullZ() const;

  //Returns vector without x
  Vec2<T> cutX() const;

  //Returns vector without y
  Vec2<T> cutY() const;

  //Returns vector without z
  Vec2<T> cutZ() const;

  //Vector equals
  bool operator==(const Vec3<T>& vector) const;

  //Vector not equals
  bool operator!=(const Vec3<T>& vector) const;

  //TODO: Description
  Vec3<T> operator+(const T) const;

  //
  template <typename U>
  Vec3<T> operator+(const U) const;

  //
  Vec3<T> operator+(const Vec3<T>&) const;

  //
  template <typename U>
  Vec3<T> operator+(const Vec3<U>&) const;

  //
  Vec3<T> operator-(const T) const;

  //
  template <typename U>
  Vec3<T> operator-(const U) const;

  //
  Vec3<T> operator-(const Vec3<T>&) const;

  //
  template <typename U>
  Vec3<T> operator-(const Vec3<U>&) const;

  //
  Vec3<T> operator*(const T) const;

  //
  template <typename U>
  Vec3<T> operator*(const U) const;

  //
  Vec3<T> operator*(const Vec3<T>&) const;

  //
  template <typename U>
  Vec3<T> operator*(const Vec3<U>&) const;

  //
  Vec3<T> operator/(const T) const;

  //
  template <typename U>
  Vec3<T> operator/(const U) const;

  //
  Vec3<T> operator/(const Vec3<T>&) const;

  //
  template <typename U>
  Vec3<T> operator/(const Vec3<U>&) const;

  //
  Vec3<T> operator%(const T) const;

  //
  template <typename U>
  Vec3<T> operator%(const U) const;

  //
  Vec3<T> operator%(const Vec3<T>&) const;

  //
  template <typename U>
  Vec3<T> operator%(const Vec3<U>&) const;

  //
  void operator=(const Vec3<T>&);

  //
  template<typename U>
  void operator=(const Vec3<U>&);

  //
  void operator+=(const T);

  //
  template <typename U>
  void operator+=(const U);

  //
  void operator+=(const Vec3<T>&);

  //
  template<typename U>
  void operator+=(const Vec3<U>&);

  //
  void operator-=(const T);

  //
  template <typename U>
  void operator-=(const U);

  //
  void operator-=(const Vec3<T>&);

  //
  template<typename U>
  void operator-=(const Vec3<U>&);

  //
  void operator*=(const T);

  //
  template<typename U>
  void operator*=(const U);

  //
  void operator*=(const Vec3<T>&);

  //
  template<typename U>
  void operator*=(const Vec3<U>&);

  //
  void operator/=(const T);

  //
  template<typename U>
  void operator/=(const U);

  //
  void operator/=(const Vec3<T>&);

  //
  template<typename U>
  void operator/=(const Vec3<U>&);

  //
  void operator%=(const T);

  //
  template<typename U>
  void operator%=(const U);

  //
  void operator%=(const Vec3<T>&);

  //
  template<typename U>
  void operator%=(const Vec3<U>&);
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
