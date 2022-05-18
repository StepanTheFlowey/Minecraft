#pragma once

#include "Vertex2.hpp"
#include "Vertex3.hpp"
#include "glad.h"

template <typename V>
class VertexConfig {
public:

  GLenum vertexSize = 0;
  GLenum vertexType = 0;
  GLenum vertexStride = 0;
  GLenum vertexOffset = 0;

  GLenum texSize = 2;
  GLenum texType = 0;
  GLenum texStride = 0;
  GLenum texOffset = 0;

  GLenum colorSize = 4;
  GLenum colorType = GL_UNSIGNED_BYTE;
  GLenum colorStride = 0;
  GLenum colorOffset = 0;

  constexpr VertexConfig();
};

#include "VertexConfig.inl"
