#pragma once

#include "Color.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Block.hpp"

class BlockRenderer {
  GLuint bufferHandle_ = 0;
  GLuint indexHandle_ = 0;
  GLsizei size_ = 0;

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
  void computeBuffer(Block** const blocks);

  //
  void draw() const;
};
