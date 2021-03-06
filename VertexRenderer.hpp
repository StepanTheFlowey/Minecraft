#pragma once

#include "main.hpp"
#include "VertexBuffer.hpp"
#include "VertexConfig.hpp"

template <typename V>
class VertexRenderer {
public:

  VertexRenderer();

  virtual ~VertexRenderer();

  virtual void update(const VertexBuffer<V>& buffer) = 0;

  virtual void draw() const = 0;
protected:

  static VertexConfig<V> config_;
};

#include "VertexRenderer.inl"
