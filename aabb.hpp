#pragma once
#include "vec.hpp"
#include "color.hpp"

template <typename T> class Aabb {
public:
  T minX;
  T minY;
  T minZ;
  T maxX;
  T maxY;
  T maxZ;

  Aabb():minX(0), minY(0), minZ(0), maxX(0), maxY(0), maxZ(0) {

  }

  Aabb(T x0, T y0, T z0, T x1, T y1, T z1) {
    minX = x0;
    minY = y0;
    minZ = z0;
    maxX = x1;
    maxY = y1;
    maxZ = z1;
  }

  Aabb(Vec3<T> v0, Vec3<T> v1) {
    minX = std::min(v0.x, v1.x);
    minY = std::min(v0.y, v1.y);
    minZ = std::min(v0.z, v1.z);
    maxX = std::max(v0.x, v1.x);
    maxY = std::max(v0.y, v1.y);
    maxZ = std::max(v0.z, v1.z);
  }

  bool intersects(Aabb<T> aabb) const {
    return intersects(aabb.minX, aabb.minY, aabb.minZ, aabb.maxX, aabb.maxY, aabb.maxZ);
  }

  template<typename U> bool intersects(Aabb<U> aabb) const {
    return intersects(static_cast<T>(aabb.minX),
                      static_cast<T>(aabb.minY),
                      static_cast<T>(aabb.minZ),
                      static_cast<T> (aabb.maxX),
                      static_cast<T>(aabb.maxY),
                      static_cast<T>(aabb.maxZ));
  }

  bool intersects(T x0, T y0, T z0, T x1, T y1, T z1) const {
    return
      (minX < x1) &&
      (maxX > x0) &&
      (minY < y1) &&
      (maxY > y0) &&
      (minZ < z1) &&
      (maxZ > z0);
  }

  void drawColorf(Color color) const {
    const GLfloat iX = static_cast<GLfloat>(minX) - 0.001F;
    const GLfloat iY = static_cast<GLfloat>(minY) - 0.001F;
    const GLfloat iZ = static_cast<GLfloat>(minZ) - 0.001F;
    const GLfloat aX = static_cast<GLfloat>(maxX) + 0.001F;
    const GLfloat aY = static_cast<GLfloat>(maxY) + 0.001F;
    const GLfloat aZ = static_cast<GLfloat>(maxZ) + 0.001F;

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

  void drawColord(Color color) const {
    const GLdouble iX = static_cast<GLdouble>(minX) - 0.001;
    const GLdouble iY = static_cast<GLdouble>(minY) - 0.001;
    const GLdouble iZ = static_cast<GLdouble>(minZ) - 0.001;
    const GLdouble aX = static_cast<GLdouble>(maxX) + 0.001;
    const GLdouble aY = static_cast<GLdouble>(maxY) + 0.001;
    const GLdouble aZ = static_cast<GLdouble>(maxZ) + 0.001;

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

  void drawAxisf() const {
    const GLfloat iX = static_cast<GLfloat>(minX) - 0.001F;
    const GLfloat iY = static_cast<GLfloat>(minY) - 0.001F;
    const GLfloat iZ = static_cast<GLfloat>(minZ) - 0.001F;
    const GLfloat aX = static_cast<GLfloat>(maxX) + 0.001F;
    const GLfloat aY = static_cast<GLfloat>(maxY) + 0.001F;
    const GLfloat aZ = static_cast<GLfloat>(maxZ) + 0.001F;

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

  void drawAxisd() {
    GLdouble iX = static_cast<GLdouble>(minX) - 0.001;
    GLdouble iY = static_cast<GLdouble>(minY) - 0.001;
    GLdouble iZ = static_cast<GLdouble>(minZ) - 0.001;
    GLdouble aX = static_cast<GLdouble>(maxX) + 0.001;
    GLdouble aY = static_cast<GLdouble>(maxY) + 0.001;
    GLdouble aZ = static_cast<GLdouble>(maxZ) + 0.001;

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
};