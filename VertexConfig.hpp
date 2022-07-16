#pragma once

#include "Vertex2.hpp"
#include "Vertex3.hpp"
#include "glad.h"

template <typename V>
struct VertexConfig {
  GLint   vertexSize = 0;
  GLenum  vertexType = 0;
  GLsizei vertexStride = 0;
  void*   vertexOffset = 0;

  GLint   texSize = 2;
  GLenum  texType = 0;
  GLsizei texStride = 0;
  void*   texOffset = 0;

  GLint   colorSize = 4;
  GLenum  colorType = GL_UNSIGNED_BYTE;
  GLsizei colorStride = 0;
  void*   colorOffset = 0;

  constexpr VertexConfig();
};

#include "VertexConfig.inl"
