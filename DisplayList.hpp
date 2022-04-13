#pragma once

#include "glad.h"

class DisplayList {
  GLuint handle_ = 0;
public:

  inline DisplayList() {
    handle_ = glGenLists(1);
  }

  inline explicit DisplayList(const GLenum mode) {
    handle_ = glGenLists(1);
    glNewList(handle_, mode);
  }

  inline ~DisplayList() {
    glDeleteLists(handle_, 1);
  }

  inline void begin() const {
    glNewList(handle_, GL_COMPILE);
  }

  inline void begin(const GLenum mode) const {
    glNewList(handle_, mode);
  }

  inline void end() const {
    glEndList();
  }

  inline void call() const {
    glCallList(handle_);
  }
};
