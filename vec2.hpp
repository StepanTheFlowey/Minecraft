#pragma once
#include <cmath>
#include <iostream>

#include <GL/GL.h>
#include <SFML/System/Vector2.hpp>

//Two component vector
template <typename T> class Vec2 {
public:
  T x;
  T y;

  //TODO: Description
  Vec2();

  //TODO: Description
  Vec2(T X, T Y);

  //TODO: Description
  template <typename U> Vec2(const Vec2<U>&);

  //TODO: Description
  template <typename U> Vec2(const sf::Vector2<U>&);

  //TODO: Description
  void print() const;

  //TODO: Description
  void print(std::string str) const;

  //TODO: Description
  void wprint() const;

  //TODO: Description
  void wprint(std::wstring str) const;

  //TODO: Description
  Vec2<T> operator+(const Vec2<T>& r);

  //TODO: Description
  template <typename U> Vec2<T> operator+(const Vec2<U>&);

  //TODO: Description
  Vec2<T> operator-(const Vec2<T>& r);

  //TODO: Description
  template <typename U> Vec2<T> operator-(const Vec2<U>&);

  //TODO: Description
  Vec2<T> operator*(const T r);

  //TODO: Description
  Vec2<T> operator*(const Vec2<T>& r);

  //TODO: Description
  template <typename U> Vec2<T> operator*(const Vec2<U>&);

  //TODO: Description
  Vec2<T> operator/(const T r);

  //TODO: Description
  Vec2<T> operator/(const Vec2<T>& r);

  //TODO: Description
  template <typename U> Vec2<T> operator/(const Vec2<U>&);

  //TODO: Description
  Vec2<T> operator%(const T r);

  //TODO: Description
  Vec2<T> operator%(const Vec2<T>& r);

  //TODO: Description
  template <typename U> Vec2<T> operator%(const Vec2<U>&);

  //TODO: Description
  void operator=(const Vec2<T>& r);

  //TODO: Description
  template <typename U> void operator=(const Vec2<U>&);

  //TODO: Description
  void operator+=(const Vec2<T>& r);

  //TODO: Description
  template <typename U> void operator+=(const Vec2<U>&);

  //TODO: Description
  void operator-=(const Vec2<T>& r);

  //TODO: Description
  template <typename U> void operator-=(const Vec2<U>&);

  //TODO: Description
  void operator*=(const T r);

  //TODO: Description
  void operator*=(const Vec2<T>& r);

  //TODO: Description
  template <typename U> void operator*=(const Vec2<U>&);

  //TODO: Description
  void operator/=(const T r);

  //TODO: Description
  void operator/=(const Vec2<T>& r);

  //TODO: Description
  template <typename U> void operator/=(const Vec2<U>&);

  //TODO: Description
  void operator%=(const T r);

  //TODO: Description
  void operator%=(const Vec2<T>& r);

  //TODO: Description
  template <typename U> void operator%=(const Vec2<U>&);
};

using Vec2f = Vec2<GLfloat>;
using Vec2d = Vec2<GLdouble>;