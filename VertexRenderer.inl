#pragma once

template <typename V>
VertexRenderer<V>::VertexRenderer() {
  debug(L"VertexRenderer()");
}

template <typename V>
VertexRenderer<V>::~VertexRenderer() {
  debug(L"~VertexRenderer()");
}

template <typename V>
VertexConfig<V> VertexRenderer<V>::config_;
