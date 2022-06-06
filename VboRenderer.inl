#pragma once

#include "Vertex2.hpp"
#include "Vertex3.hpp"
#include "VboRenderer.hpp"

template<typename V>
VboRenderer<V>::VboRenderer() {
  debug(L"VboRenderer()");

  glGenBuffers(1, &handle_);
}

template<typename V>
VboRenderer<V>::~VboRenderer() {
  debug(L"~VboRenderer()");

  glDeleteBuffers(1, &handle_);
}

template<typename V>
void VboRenderer<V>::update(const VertexBuffer<V>& buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, handle_);
  glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(V), buffer.data(), GL_STATIC_DRAW);
}

template<typename V>
inline void VboRenderer<V>::draw() const {
  glBindBuffer(GL_ARRAY_BUFFER, handle_);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(config_.vertexSize, config_.vertexType, config_.vertexStride, config_.vertexOffset);
  glTexCoordPointer(2, GL_SHORT, 14, (void*)6);
  glColorPointer(4, GL_UNSIGNED_BYTE, 14, (void*)10);

  glDrawArrays(GL_QUADS, 0, size_);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
