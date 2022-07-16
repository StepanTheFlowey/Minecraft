#pragma once

template<typename V>
constexpr VertexConfig<V>::VertexConfig() {
  GLsizei bytesPerVertex = 0;
  if(std::is_same_v<V::V, int16_t>) {
    vertexType = GL_SHORT;
    bytesPerVertex = 2;
  }
  else if(std::is_same_v<V::V, int32_t>) {
    vertexType = GL_INT;
    bytesPerVertex = 4;
  }
  else if(std::is_same_v<V::V, float_t>) {
    vertexType = GL_FLOAT;
    bytesPerVertex = 4;
  }
  else if(std::is_same_v<V::V, double_t>) {
    vertexType = GL_DOUBLE;
    bytesPerVertex = 8;
  }
  else {
    static_assert(false);
  }

  GLsizei bytesPerTex = 0;
  if(std::is_same_v<V::T, int16_t>) {
    texType = GL_SHORT;
    bytesPerTex = 2;
  }
  else if(std::is_same_v<V::T, int32_t>) {
    texType = GL_INT;
    bytesPerTex = 4;
  }
  else if(std::is_same_v<V::T, float_t>) {
    texType = GL_FLOAT;
    bytesPerTex = 4;
  }
  else if(std::is_same_v<V::T, double_t>) {
    texType = GL_DOUBLE;
    bytesPerTex = 8;
  }
  else {
    static_assert(false);
  }

  GLsizei bytesPerColor = 0;
  if(std::is_same_v<V::C, Color>) {
    colorType = GL_UNSIGNED_BYTE;
    bytesPerColor = 1;
  }
  else {
    static_assert(false);
  }

  if(std::is_same_v<Vertex2<V::V, V::T, V::C>, V>) {
    vertexSize = 2;
  }
  else if(std::is_same_v<Vertex3<V::V, V::T, V::C>, V>) {
    vertexSize = 3;
  }
  else {
    static_assert(false);
  }

  bytesPerVertex *= vertexSize;
  bytesPerTex *= texSize;
  bytesPerColor *= colorSize;

  GLsizei stride = bytesPerVertex + bytesPerTex + bytesPerColor;
  vertexStride = stride;
  texStride = stride;
  colorStride = stride;

  texOffset = stride - bytesPerVertex - bytesPerColor;
  colorOffset = stride - bytesPerVertex - bytesPerTex;
}
