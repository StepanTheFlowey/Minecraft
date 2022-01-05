#pragma once

#include "color.hpp"
#include "vec3.hpp"
#include "glHelper.hpp"

class Renderer {
public:

  //
  Renderer();

  //
  ~Renderer();

  //
  virtual void draw();
};