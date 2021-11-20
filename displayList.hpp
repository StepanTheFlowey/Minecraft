#pragma once
#include "types.hpp"

class DisplayList {
  GLuint handle_ = 0;
public:
  DisplayList() {
    handle_ = glGenLists(1);
  }

  explicit DisplayList(GLenum mode) {
    handle_ = glGenLists(1);
    glNewList(handle_, mode);
  }

  void begin() {
    glNewList(handle_, GL_COMPILE);
  }

  void begin(GLenum mode) {
    glNewList(handle_, mode);
  }

  void end() {
    glEndList();
  }

  void call() {
    glCallList(handle_);
  }
};