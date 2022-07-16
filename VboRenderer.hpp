#pragma once

#include "main.hpp"
#include "glad.h"
#include "VertexRenderer.hpp"

template <typename V>
class VboRenderer : public VertexRenderer<V> {
public:

  VboRenderer();

  virtual ~VboRenderer();

  virtual void update(const VertexBuffer<V>& buffer) override;

  virtual void draw() const override;
protected:

  GLuint handle_ = 0;
  GLsizei size_ = 0;
};

#include "VboRenderer.inl"
