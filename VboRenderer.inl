#pragma once

template <typename V>
VboRenderer<V>::VboRenderer() {
  debug(L"VboRenderer()");

  glGenBuffers(1, &handle_);
}

template <typename V>
VboRenderer<V>::~VboRenderer() {
  debug(L"~VboRenderer()");

  glDeleteBuffers(1, &handle_);
}

template <typename V>
void VboRenderer<V>::update(const VertexBuffer<V>& buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, handle_);
  glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(V), buffer.data(), GL_STATIC_DRAW);

  size_ = buffer.size();
}

template <typename V>
void VboRenderer<V>::draw() const {
  glBindBuffer(GL_ARRAY_BUFFER, handle_);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(config_.vertexSize, config_.vertexType, config_.vertexStride, config_.vertexOffset);
  glTexCoordPointer(config_.texSize, config_.texType, config_.texStride, config_.texOffset);
  glColorPointer(config_.colorSize, config_.colorType, config_.colorStride, config_.colorOffset);

  glDrawArrays(GL_QUADS, 0, size_);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
