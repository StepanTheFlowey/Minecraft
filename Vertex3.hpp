#pragma once

#include "Vec3.hpp"
#include "Vec2.hpp"
#include "Color.hpp"

//Class of 3D vertex
//C - color class not type of value in class
template <typename V, typename T, typename C>
struct Vertex3 {
  Vec3<V> vertex;
  Vec2<T> texture;
  C color;

  using V = V;
  using T = T;
  using C = C;
};
