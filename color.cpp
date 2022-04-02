#pragma once

#include "color.hpp"

Color::Color() {
  r = 0;
  g = 0;
  b = 0;
  a = 255;
}

Color::Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) {
  r = R;
  g = G;
  b = B;
  a = A;
}
