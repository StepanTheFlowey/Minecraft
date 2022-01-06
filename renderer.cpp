#include "renderer.hpp"

Renderer::Renderer() {
#ifdef DEBUG
  std::wcout << L"Renderer()" << std::endl;
#endif // DEBUG
}

Renderer::~Renderer() {
#ifdef DEBUG
  std::wcout << L"~Renderer()" << std::endl;
#endif // DEBUG
}

inline void Renderer::draw() const {
  throw;
}