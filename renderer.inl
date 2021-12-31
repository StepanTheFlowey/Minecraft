#pragma once

#include "renderer.hpp"

inline Renderer::Renderer() {

}

inline Renderer::~Renderer() {

}

inline void Renderer::create(GLsizei colorSize, GLsizei textureSize, GLsizei vertexSize, GLenum usage) {
  cSize_ = colorSize;
  tSize_ = textureSize;
  vSize_ = vertexSize;
  glGenBuffersARB(1, &handle_);
  glBindBufferARB(GL_ARRAY_BUFFER, handle_);
  glBufferDataARB(GL_ARRAY_BUFFER, cSize_ + tSize_ + vSize_, NULL, usage);
}

inline void Renderer::update(size_t offset, size_t size, void* data) const {
  glBindBufferARB(GL_ARRAY_BUFFER, handle_);
  glBufferSubDataARB(GL_ARRAY_BUFFER, offset, size, data);
}

inline void Renderer::destroy() {
  glDeleteBuffersARB(1, &handle_);
}

inline void Renderer::draw(GLenum drawType, GLenum vertexDataType, GLsizei vertexCount) const {
  glBindBufferARB(GL_ARRAY_BUFFER, handle_);

  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  glColorPointer(4, GL_UNSIGNED_BYTE, 0, (void*) cSize_);
  glTexCoordPointer(3, GL_SHORT, cSize_, (void*) tSize_);
  glVertexPointer(3, vertexDataType, cSize_ + tSize_, (void*) vSize_);

  glDrawArrays(drawType, 0, vertexCount);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}