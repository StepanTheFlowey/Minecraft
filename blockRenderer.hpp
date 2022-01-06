#pragma once

#include "renderer.hpp"
#include "color.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "rect3.hpp"
#include "block.hpp"

enum class GameMode {
  Null = 0,
  Survival = 1,
  Creative = 2
};

class BlockRenderer : public Renderer {
  GLuint bufferHandle_ = 0;
  GLuint indexHandle_ = 0;
  size_t size_ = 0;
public:

  struct Vertex {
    Vec3<int16_t> vertex;
    Vec2<int16_t> texture;
    Color color;
  };
  
  //
  BlockRenderer();

  //
  ~BlockRenderer();

  //
  void computeBuffer(BlockRenderInfo*);

  //
  virtual void draw() const override;
};