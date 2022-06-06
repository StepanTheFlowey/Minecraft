#pragma once

#include "main.hpp"
#include "VertexRenderer.hpp"
#include "glad.h"

template <typename V>
class VboRenderer : public VertexRenderer<V> {
public:

  VboRenderer();

  virtual ~VboRenderer();

  virtual void update(const VertexBuffer<V>& buffer);

  virtual void draw();
protected:

  GLuint handle_ = 0;
};

#include "VboRenderer.inl"
