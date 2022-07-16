#include "DisplayList.hpp"

DisplayList::DisplayList() {
  handle_ = glGenLists(1);
}

DisplayList::DisplayList(const GLenum mode) {
  handle_ = glGenLists(1);
  glNewList(handle_, mode);
}

DisplayList::~DisplayList() {
  glDeleteLists(handle_, 1);
}

void DisplayList::begin() {
  glNewList(handle_, GL_COMPILE);
}

void DisplayList::begin(const GLenum mode) {
  glNewList(handle_, mode);
}

void DisplayList::end() {
  glEndList();
}

void DisplayList::call() const {
  glCallList(handle_);
}
