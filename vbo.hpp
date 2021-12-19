#pragma once

#include "types.hpp"
#include "color.hpp"
#include "glInfo.h"

template <typename T> class Vbo {
  GLenum vtType_;
  GLenum vtUsage_;
  GLsizei vtSize_;
  GLuint buff_;
public:
  Vbo() {
    vtType_ = 0;
    vtUsage_ = 0;
    vtSize_ = 0;
  }

  Vbo(GLenum vtType,GLenum vtUsage,GLsizei vtSize) {
    vtType_ = vtType;
    vtUsage_ = vtUsage;
    vtSize_ = vtSize;
  }

  ~Vbo() {

  }

  void setVertexType(GLenum vtType) {
    vtType_ = vtType;
  }

  void setUsage(GLenum vtUsage) {
    vtUsage_ = vtUsage;
  }

  void setSize(GLenum vtSize) {
    vtSize_ = vtSize;
  }

  void create() {
    glGenBuffersARB(1, &buff_);
    glBindBufferARB(GL_ARRAY_BUFFER,buff_);
  }
};