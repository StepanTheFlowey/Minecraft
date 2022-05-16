#pragma once

#include "VertexRenderer.hpp"

template <typename V>
class ImmediateRenderer : public VertexRenderer<V> {
public:

  inline ImmediateRenderer();

  inline ~ImmediateRenderer();
};
