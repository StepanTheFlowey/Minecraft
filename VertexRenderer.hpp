#pragma once

#include "main.hpp"
#include "VertexBuffer.hpp"

template <typename V>
class VertexRenderer {
public:
 
  inline VertexRenderer() {
    debug(L"VertexRenderer()");
  }

  inline ~VertexRenderer() {
    debug(L"~VertexRenderer()");
  }

};
