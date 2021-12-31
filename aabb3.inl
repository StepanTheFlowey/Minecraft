#pragma once

template <typename T>
Aabb3<T>::Aabb3() {

}

template <typename T> 
Aabb3<T>::Aabb3(T x0, T y0, T z0, T x1, T y1, T z1) {
  setComponent(x0, y0, z0, x1, y1, z1);
}

template <typename T> 
Aabb3<T>::Aabb3(const Vec3<T> _min, const Vec3<T> _max) {
  setVector(_min, _max);
}

template <typename T> 
Aabb3<T>::Aabb3(const Aabb3<T>& aabb) {
  min = aabb.min;
  max = aabb.max;
}

template <typename T> template <typename U>
Aabb3<T>::Aabb3(const Aabb3<U>& aabb) {
  min = Vec3<T>(aabb.min);
  max = Vec3<T>(aabb.max);
}

template <typename T>
void Aabb3<T>::setComponent(T x0, T y0, T z0, T x1, T y1, T z1) {
  min.x = std::min(x0, x1);
  min.y = std::min(y0, y1);
  min.z = std::min(z0, z1);
  max.x = std::max(x0, x1);
  max.y = std::max(y0, y1);
  max.z = std::max(z0, z1);
}

template <typename T>
void Aabb3<T>::setVector(const Vec3<T> _min, const Vec3<T> _max) {
  setComponent(_min.x, _min.y, _min.z, _max.x, _max.y, _max.z);
}

template <typename T>
bool Aabb3<T>::intersects(const Aabb3<T> aabb) const {
  return intersects(aabb.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb.max.z);
}

template <typename T> template <typename U>
bool Aabb3<T>::intersects(const Aabb3<U> aabb) const {
  return intersects(static_cast<T>(aabb.min.x),
                    static_cast<T>(aabb.min.y),
                    static_cast<T>(aabb.min.z),
                    static_cast<T>(aabb.max.x),
                    static_cast<T>(aabb.max.y),
                    static_cast<T>(aabb.max.z));
}

template <typename T> 
bool Aabb3<T>::intersects(T x0, T y0, T z0, T x1, T y1, T z1) const {
  return
    (min.x < x1) &&
    (max.x > x0) &&
    (min.y < y1) &&
    (max.y > y0) &&
    (min.z < z1) &&
    (max.z > z0);
}

template <typename T> 
void Aabb3<T>::drawColorf(const Color color) const {
  const GLfloat iX = static_cast<GLfloat>(min.x) - 0.001F;
  const GLfloat iY = static_cast<GLfloat>(min.y) - 0.001F;
  const GLfloat iZ = static_cast<GLfloat>(min.z) - 0.001F;
  const GLfloat aX = static_cast<GLfloat>(max.x) + 0.001F;
  const GLfloat aY = static_cast<GLfloat>(max.y) + 0.001F;
  const GLfloat aZ = static_cast<GLfloat>(max.z) + 0.001F;

  glBegin(GL_LINES);

  color.glColor();
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
void Aabb3<T>::drawColord(const Color color) const {
  const GLdouble iX = static_cast<GLdouble>(min.x) - 0.001;
  const GLdouble iY = static_cast<GLdouble>(min.y) - 0.001;
  const GLdouble iZ = static_cast<GLdouble>(min.z) - 0.001;
  const GLdouble aX = static_cast<GLdouble>(max.x) + 0.001;
  const GLdouble aY = static_cast<GLdouble>(max.y) + 0.001;
  const GLdouble aZ = static_cast<GLdouble>(max.z) + 0.001;

  glBegin(GL_LINES);

  color.glColor();
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
void Aabb3<T>::drawAxisf() const {
  const GLfloat iX = static_cast<GLfloat>(min.x) - 0.001F;
  const GLfloat iY = static_cast<GLfloat>(min.y) - 0.001F;
  const GLfloat iZ = static_cast<GLfloat>(min.z) - 0.001F;
  const GLfloat aX = static_cast<GLfloat>(max.x) + 0.001F;
  const GLfloat aY = static_cast<GLfloat>(max.y) + 0.001F;
  const GLfloat aZ = static_cast<GLfloat>(max.z) + 0.001F;

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
void Aabb3<T>::drawAxisd() const {
  GLdouble iX = static_cast<GLdouble>(min.x) - 0.001;
  GLdouble iY = static_cast<GLdouble>(min.y) - 0.001;
  GLdouble iZ = static_cast<GLdouble>(min.z) - 0.001;
  GLdouble aX = static_cast<GLdouble>(max.x) + 0.001;
  GLdouble aY = static_cast<GLdouble>(max.y) + 0.001;
  GLdouble aZ = static_cast<GLdouble>(max.z) + 0.001;

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