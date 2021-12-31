#pragma once

#include "types.hpp"

#include <gl/GL.h>
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
  Vec2(const Vec2<T>&);

  //Different type copy constructor
  template <typename U>
  Vec2(const Vec2<U>&);

  //SFML compitaability constructor
  Vec2(const sf::Vector2<T>&);

  //SFML different type compitablity constructor
  template <typename U>
  Vec2(const sf::Vector2<U>&);

  //Prints vector components
  void print() const;

  //Prints string and vector component
  void print(std::string) const;

  //Prints vector component
  void wprint() const;

  //Prints string and vector component
  void wprint(std::wstring) const;

  //
  Vec2<T> abs() const;

  //
  double_t lenght() const;

  //
  Vec2<T> normalize() const;

  //
  double_t distanceTo(Vec2<T> vector) const;

  //Calls glVertex2d(x, y)
  void glVertex()const;

  //Scalar add operator
  Vec2<T> operator+(const T) const;

  //Different type scalar add operator
  template <typename U>
  Vec2<T> operator+(const U) const;

  //Vector add operator
  Vec2<T> operator+(const Vec2<T>&) const;

  //Different type vector add operator
  template <typename U>
  Vec2<T> operator+(const Vec2<U>&) const;

  //Scalar substract operator
  Vec2<T> operator-(const T) const;

  //Different type scalar substract operator
  template <typename U>
  Vec2<T> operator-(const U) const;

  //Vector substract operator
  Vec2<T> operator-(const Vec2<T>&) const;

  //Different type vector substract operator
  template <typename U>
  Vec2<T> operator-(const Vec2<U>&) const;

  //Scalar multiply operator
  Vec2<T> operator*(const T) const;

  //Different type scalar multiply operator
  template <typename U>
  Vec2<T> operator*(const U) const;

  //Vector multiply operator
  Vec2<T> operator*(const Vec2<T>&) const;

  //Different type vector multiply operator
  template <typename U>
  Vec2<T> operator*(const Vec2<U>&) const;

  //Scalar divide operator
  Vec2<T> operator/(const T) const;

  //Different type scalar divide operator
  template <typename U>
  Vec2<T> operator/(const U) const;

  //Vector divide operator
  Vec2<T> operator/(const Vec2<T>&) const;

  //Different type vector divide operator
  template <typename U>
  Vec2<T> operator/(const Vec2<U>&) const;

  //Scalar modulo operator
  Vec2<T> operator%(const T) const;

  //Different type scalar modulo operator
  template <typename U>
  Vec2<T> operator%(const U) const;

  //Vector modulo operator
  Vec2<T> operator%(const Vec2<T>&) const;

  //Different type vector modulo operator
  template <typename U>
  Vec2<T> operator%(const Vec2<U>&) const;

  //Assignment operator
  void operator=(const Vec2<T>&);

  //Different operator assignment operator
  template <typename U>
  void operator=(const Vec2<U>&);

  //TODO: Description
  void operator+=(const Vec2<T>&);

  //
  template <typename U>
  void operator+=(const Vec2<U>&);

  //
  void operator-=(const Vec2<T>&);

  //
  template <typename U>
  void operator-=(const Vec2<U>&);

  //
  void operator*=(const T);

  //
  template <typename U>
  void operator*=(const U);

  //
  void operator*=(const Vec2<T>&);

  //
  template <typename U>
  void operator*=(const Vec2<U>&);

  //
  void operator/=(const T);

  //
  template <typename U>
  void operator/=(const U);

  //
  void operator/=(const Vec2<T>&);

  //
  template <typename U>
  void operator/=(const Vec2<U>&);

  //
  void operator%=(const T);

  //
  template <typename U>
  void operator%=(const U);

  //
  void operator%=(const Vec2<T>&);

  //
  template <typename U>
  void operator%=(const Vec2<U>&);
};

#include "vec2.inl"

using Vec2f = Vec2<GLfloat>;
using Vec2d = Vec2<GLdouble>;