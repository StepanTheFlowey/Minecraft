#pragma once

#include "glad.h"

class Color {
public:

  GLubyte r = 0;
  GLubyte g = 0;
  GLubyte b = 0;
  GLubyte a = 255;

  //Default constructor
  constexpr Color() = default;

  //Default destructor
  constexpr Color(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a = 255);

  //Calls glColor(r,g,b,a)
  inline void glColor() const;
};

#include "Color.inl"
