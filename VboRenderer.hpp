#pragma once

#include "main.hpp"
#include "VertexRenderer.hpp"

template <typename V>
class VboRenderer : public VertexRenderer<V> {
public:

  VboRenderer() {
    debug(L"VboRenderer()")
  }

  ~VboRenderer() {
    debug(L"~VboRenderer()");
  }

  void setBuffer(const VertexBuffer<V>& buffer);

  void update();

  void draw();
};
