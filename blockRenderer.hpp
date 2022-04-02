#pragma once

#include "renderer.hpp"
#include "color.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "rect3.hpp"
#include "block.hpp"

class BlockRenderer : public Renderer {
  GLuint bufferHandle_ = 0;
  GLuint indexHandle_ = 0;
  size_t size_ = 0;

  struct Vertex {
    Vec3<int16_t> vertex;
    Vec2<int16_t> texture;
    Color color;
  };
public:
  
  //
  BlockRenderer();

  //
  ~BlockRenderer();

  //
  void computeBuffer(Block**);

  //
  virtual void draw() const override;
};
