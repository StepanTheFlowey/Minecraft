#include "Vec2.hpp"

inline void Vec2<short>::glVertex() const {
  glVertex2s(x, y);
}

inline void Vec2<int>::glVertex() const {
  glVertex2i(x, y);
}

inline void Vec2<float_t>::glVertex() const {
  glVertex2f(x, y);
}

inline void Vec2<double_t>::glVertex() const {
  glVertex2d(x, y);
}