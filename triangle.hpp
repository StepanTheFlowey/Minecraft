#pragma once
#include "vec3.hpp"

template <typename T> class Triangle {
public:
  Vec3<T> A;
  Vec3<T> B;
  Vec3<T> C;

  //Default constructor
  Triangle();

  //Component constructor
  Triangle(Vec3<T>, Vec3<T>, Vec3<T>);
  
  //Copy constructor
  Triangle(const Triangle<T> &);

  //Different type copy constructor
  template <typename U> Triangle(const Triangle<U>&);
};

using Triangled = Triangle<GLdouble>;
using Trianglef = Triangle<GLfloat>;

#include "triangle.inl"