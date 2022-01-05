#pragma once

#include "renderer.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "color.hpp"

class BlockRenderer : public Renderer {
  Color* color_;
  Vec2<int16_t>* texture_;
  Vec3<int16_t>* vertex_;
public:

  //
  BlockRenderer();

  //
  ~BlockRenderer();

  //
  virtual void draw() override;
};