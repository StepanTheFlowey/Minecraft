#pragma once

#include "types.hpp"

#include "vec2.hpp"

#include <gl/GL.h>
#include <SFML/System/Vector3.hpp>

//Three component vector
template <typename T> class Vec3 {
public:
  T x;
  T y;
  T z;

  //Default constructor
  Vec3();

  //Component constructor
  Vec3(T, T, T);

  //Copy constrcutor
  template <typename U> Vec3(const Vec3<U>&);

  //Copy constrcutor
  template <typename U> Vec3(const sf::Vector3<U>&);

  //Print to std::cout
  void print() const;

  //Print with prefix to std::cout
  void print(std::string) const;

  //Print to std::wcout
  void wprint() const;

  //Print with prefix to std::wcout
  void wprint(std::wstring) const;

  //Absolute vector
  Vec3<T> abs() const;

  //Scalar lenght of vector
  double_t lenght() const;

  //Normalizing vector
  Vec3<T> normalize() const;

  //Distance to other vector
  double_t distanceTo(const Vec3<T>) const;

  //
  T dotProduct(const Vec3<T>) const;

  //
  Vec3<T> vectorProduct(const Vec3<T>) const;

  //Call glVertex3d(x,y,z)
  void glVertex() const;

  //
  Vec3<T> nullX() const;

  //
  Vec3<T> nullY() const;

  //
  Vec3<T> nullZ() const;

  //
  Vec2<T> cutX() const;

  //
  Vec2<T> cutY() const;

  //
  Vec2<T> cutZ() const;

  //Vector equals
  bool operator==(const Vec3<T>&) const;

  //Vector not equals
  bool operator!=(const Vec3<T>&) const;

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

#include "vec3.inl"

using Vec3f = Vec3<GLfloat>;
using Vec3d = Vec3<GLdouble>;