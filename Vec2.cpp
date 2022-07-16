#include "Vec2.hpp"

void Vec2<short>::glVertex() const {
  glVertex2s(x, y);
}

void Vec2<int>::glVertex() const {
  glVertex2i(x, y);
}

void Vec2<float_t>::glVertex() const {
  glVertex2f(x, y);
}

void Vec2<double_t>::glVertex() const {
  glVertex2d(x, y);
}
