#pragma once

#include "glad.h"

class Color {
public:

  GLubyte r;
  GLubyte g;
  GLubyte b;
  GLubyte a;

  //Default constructor
  inline Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 255;
  }

  //Default destructor
  inline Color(const GLubyte R, const GLubyte G, const GLubyte B, const GLubyte A = 255) {
    r = R;
    g = G;
    b = B;
    a = A;
  }

  //Calls glColor(r,g,b,a)
  inline void glColor() const {
    glColor4ub(r, g, b, a);
  }
};
