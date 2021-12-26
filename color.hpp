#pragma once

#include <Windows.h>
#include <gl/GL.h>

class Color {
public:
  GLubyte r;
  GLubyte g;
  GLubyte b;
  GLubyte a;

  //Default constructor
  Color();

  //Default destructor
  Color(GLubyte, GLubyte, GLubyte, GLubyte = 255);

  //Calls glColor(r,g,b,a)
  inline void glColor() const;
};


inline void Color::glColor() const {
  glColor4ub(r, g, b, a);
}