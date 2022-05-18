#pragma once

#include "main.hpp"
#include "VertexBuffer.hpp"
#include "VertexConfig.hpp"

template <typename V>
class VertexRenderer {
public:

  inline VertexRenderer();

  virtual ~VertexRenderer();

  virtual void update(const VertexBuffer<V> buffer) = 0;

  virtual void draw(const VertexConfig<V> config) const = 0;
};

#include "VertexRenderer.inl"
