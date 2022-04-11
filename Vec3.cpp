#include "Vec3.hpp"

inline void Vec3<short>::glVertex() const {
  glVertex3s(x, y, z);
}

inline void Vec3<int>::glVertex() const {
  glVertex3i(x, y, z);
}

inline void Vec3<float_t>::glVertex() const {
  glVertex3f(x, y, z);
}

inline void Vec3<double_t>::glVertex() const {
  glVertex3d(x, y, z);
}