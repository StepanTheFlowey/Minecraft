#pragma once

constexpr Color::Color() {

}

constexpr Color::Color(const GLubyte _r, const GLubyte _g, const GLubyte _b, const GLubyte _a) {
  r = _r;
  g = _g;
  b = _b;
  a = _a;
}

inline void Color::glColor() const {
  glColor4ub(r, g, b, a);
}
