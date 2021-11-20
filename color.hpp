#pragma once
#include <gl\GL.h>
#include <inttypes.h>

class Color {
public:
  GLubyte r;
  GLubyte g;
  GLubyte b;
  GLubyte a;

  Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 255;
  }

  Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A = 255) {
    r = R;
    g = G;
    b = B;
    a = A;
  }

  inline void glColor() const {
    glColor4ub(r, g, b, a);
  }
};