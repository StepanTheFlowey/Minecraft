#include "Vec3.hpp"

void Vec3<short>::glVertex() const {
  glVertex3s(x, y, z);
}

void Vec3<int>::glVertex() const {
  glVertex3i(x, y, z);
}

void Vec3<float_t>::glVertex() const {
  glVertex3f(x, y, z);
}

void Vec3<double_t>::glVertex() const {
  glVertex3d(x, y, z);
}
