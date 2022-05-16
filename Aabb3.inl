#pragma once

template <typename T>
constexpr Aabb3<T>::Aabb3() {

}

template <typename T>
constexpr Aabb3<T>::Aabb3(const Vec3<T> _min, const Vec3<T> _max) {
  set(_min, _max);
}

template <typename T> template <typename U>
constexpr Aabb3<T>::Aabb3(const Aabb3<U>& aabb) {
  min = Vec3<T>(aabb.min);
  max = Vec3<T>(aabb.max);
}

template <typename T>
inline Aabb3<T>::~Aabb3() {

}

template <typename T>
void Aabb3<T>::set(const Vec3<T> _min, const Vec3<T> _max) {
  min.x = std::min(_min.x, _max.x);
  min.y = std::min(_min.y, _max.y);
  min.z = std::min(_min.z, _max.z);
  max.x = std::max(_min.x, _max.x);
  max.y = std::max(_min.y, _max.y);
  max.z = std::max(_min.z, _max.z);
}

template <typename T>
bool Aabb3<T>::intersects(const Aabb3<T> aabb) const {
  return
    (min.x < aabb.max.x) &&
    (max.x > aabb.min.x) &&
    (min.y < aabb.max.y) &&
    (max.y > aabb.min.y) &&
    (min.z < aabb.max.z) &&
    (max.z > aabb.min.z);
}

template <typename T>
void Aabb3<T>::draw(const Color color, const float_t offset) const {
  const GLfloat iX = static_cast<GLfloat>(min.x) - offset;
  const GLfloat iY = static_cast<GLfloat>(min.y) - offset;
  const GLfloat iZ = static_cast<GLfloat>(min.z) - offset;
  const GLfloat aX = static_cast<GLfloat>(max.x) + offset;
  const GLfloat aY = static_cast<GLfloat>(max.y) + offset;
  const GLfloat aZ = static_cast<GLfloat>(max.z) + offset;

  color.glColor();

  glBegin(GL_LINES);

  glVertex3f(iX, iY, iZ);
  glVertex3f(aX, iY, iZ);

  glVertex3f(iX, iY, aZ);
  glVertex3f(aX, iY, aZ);

  glVertex3f(iX, aY, iZ);
  glVertex3f(aX, aY, iZ);

  glVertex3f(iX, aY, aZ);
  glVertex3f(aX, aY, aZ);


  glVertex3f(iX, iY, iZ);
  glVertex3f(iX, aY, iZ);

  glVertex3f(aX, iY, iZ);
  glVertex3f(aX, aY, iZ);

  glVertex3f(iX, iY, aZ);
  glVertex3f(iX, aY, aZ);

  glVertex3f(aX, iY, aZ);
  glVertex3f(aX, aY, aZ);


  glVertex3f(iX, iY, iZ);
  glVertex3f(iX, iY, aZ);

  glVertex3f(aX, iY, iZ);
  glVertex3f(aX, iY, aZ);

  glVertex3f(iX, aY, iZ);
  glVertex3f(iX, aY, aZ);

  glVertex3f(aX, aY, iZ);
  glVertex3f(aX, aY, aZ);

  glEnd();
}

template <typename T>
void Aabb3<T>::draw(const Color color, const double_t offset) const {
  const GLdouble iX = static_cast<GLdouble>(min.x) - offset;
  const GLdouble iY = static_cast<GLdouble>(min.y) - offset;
  const GLdouble iZ = static_cast<GLdouble>(min.z) - offset;
  const GLdouble aX = static_cast<GLdouble>(max.x) + offset;
  const GLdouble aY = static_cast<GLdouble>(max.y) + offset;
  const GLdouble aZ = static_cast<GLdouble>(max.z) + offset;

  color.glColor();

  glBegin(GL_LINES);

  glVertex3d(iX, iY, iZ);
  glVertex3d(aX, iY, iZ);

  glVertex3d(iX, iY, aZ);
  glVertex3d(aX, iY, aZ);

  glVertex3d(iX, aY, iZ);
  glVertex3d(aX, aY, iZ);

  glVertex3d(iX, aY, aZ);
  glVertex3d(aX, aY, aZ);


  glVertex3d(iX, iY, iZ);
  glVertex3d(iX, aY, iZ);

  glVertex3d(aX, iY, iZ);
  glVertex3d(aX, aY, iZ);

  glVertex3d(iX, iY, aZ);
  glVertex3d(iX, aY, aZ);

  glVertex3d(aX, iY, aZ);
  glVertex3d(aX, aY, aZ);


  glVertex3d(iX, iY, iZ);
  glVertex3d(iX, iY, aZ);

  glVertex3d(aX, iY, iZ);
  glVertex3d(aX, iY, aZ);

  glVertex3d(iX, aY, iZ);
  glVertex3d(iX, aY, aZ);

  glVertex3d(aX, aY, iZ);
  glVertex3d(aX, aY, aZ);

  glEnd();
}

template <typename T>
void Aabb3<T>::draw(const float_t offset) const {
  const GLfloat iX = static_cast<GLfloat>(min.x) - offset;
  const GLfloat iY = static_cast<GLfloat>(min.y) - offset;
  const GLfloat iZ = static_cast<GLfloat>(min.z) - offset;
  const GLfloat aX = static_cast<GLfloat>(max.x) + offset;
  const GLfloat aY = static_cast<GLfloat>(max.y) + offset;
  const GLfloat aZ = static_cast<GLfloat>(max.z) + offset;

  glBegin(GL_LINES);

  glColor3ub(255, 0, 0);
  glVertex3f(iX, iY, iZ);
  glVertex3f(aX, iY, iZ);

  glVertex3f(iX, iY, aZ);
  glVertex3f(aX, iY, aZ);

  glVertex3f(iX, aY, iZ);
  glVertex3f(aX, aY, iZ);

  glVertex3f(iX, aY, aZ);
  glVertex3f(aX, aY, aZ);

  glColor3ub(0, 255, 0);
  glVertex3f(iX, iY, iZ);
  glVertex3f(iX, aY, iZ);

  glVertex3f(aX, iY, iZ);
  glVertex3f(aX, aY, iZ);

  glVertex3f(iX, iY, aZ);
  glVertex3f(iX, aY, aZ);

  glVertex3f(aX, iY, aZ);
  glVertex3f(aX, aY, aZ);

  glColor3ub(0, 0, 255);
  glVertex3f(iX, iY, iZ);
  glVertex3f(iX, iY, aZ);

  glVertex3f(aX, iY, iZ);
  glVertex3f(aX, iY, aZ);

  glVertex3f(iX, aY, iZ);
  glVertex3f(iX, aY, aZ);

  glVertex3f(aX, aY, iZ);
  glVertex3f(aX, aY, aZ);

  glEnd();
}

template <typename T>
void Aabb3<T>::draw(const double_t offset) const {
  GLdouble iX = static_cast<GLdouble>(min.x) - offset;
  GLdouble iY = static_cast<GLdouble>(min.y) - offset;
  GLdouble iZ = static_cast<GLdouble>(min.z) - offset;
  GLdouble aX = static_cast<GLdouble>(max.x) + offset;
  GLdouble aY = static_cast<GLdouble>(max.y) + offset;
  GLdouble aZ = static_cast<GLdouble>(max.z) + offset;

  glBegin(GL_LINES);

  glColor3ub(255, 0, 0);
  glVertex3d(iX, iY, iZ);
  glVertex3d(aX, iY, iZ);

  glVertex3d(iX, iY, aZ);
  glVertex3d(aX, iY, aZ);

  glVertex3d(iX, aY, iZ);
  glVertex3d(aX, aY, iZ);

  glVertex3d(iX, aY, aZ);
  glVertex3d(aX, aY, aZ);

  glColor3ub(0, 255, 0);
  glVertex3d(iX, iY, iZ);
  glVertex3d(iX, aY, iZ);

  glVertex3d(aX, iY, iZ);
  glVertex3d(aX, aY, iZ);

  glVertex3d(iX, iY, aZ);
  glVertex3d(iX, aY, aZ);

  glVertex3d(aX, iY, aZ);
  glVertex3d(aX, aY, aZ);

  glColor3ub(0, 0, 255);
  glVertex3d(iX, iY, iZ);
  glVertex3d(iX, iY, aZ);

  glVertex3d(aX, iY, iZ);
  glVertex3d(aX, iY, aZ);

  glVertex3d(iX, aY, iZ);
  glVertex3d(iX, aY, aZ);

  glVertex3d(aX, aY, iZ);
  glVertex3d(aX, aY, aZ);

  glEnd();
}
