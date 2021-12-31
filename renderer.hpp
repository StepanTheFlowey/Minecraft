#pragma once

#include "color.hpp"
#include "vec3.hpp"
#include "glHelper.hpp"

class Renderer {
  GLuint handle_ = 0;
  GLsizei cSize_ = 0;
  GLsizei tSize_ = 0;
  GLsizei vSize_ = 0;
public:

  //
  Renderer();

  //
  ~Renderer();

  //
  void create(GLsizei, GLsizei, GLsizei, GLenum);

  //
  void update(size_t, size_t, void*) const;

  //
  void destroy();

  //
  void draw(GLenum, GLenum, GLsizei) const;
};

#include "renderer.inl"