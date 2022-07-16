#pragma once

#include <vector>
#include <functional>
#include "main.hpp"
#include "Vec3.hpp"
#include "Aabb3.hpp"
#include "Side.hpp"
#include "Color.hpp"
#include "Vertex3.hpp"
#include "VertexRenderer.hpp"

using blockId_t = uint16_t;   //Max 65535 blocks in one source
using sourceId_t = uint16_t;  //Max 65535 sources (e.g. mods)
using modelId_t = uint16_t;   //Max 65535 block model
using textureId_t = uint16_t; //Max 65535 textures
using blockPos_t = int32_t;   //Absolute block pos

using BlockPos = Vec3<blockPos_t>;
using BlockAabb = Aabb3<blockPos_t>;

using BlockVertex = Vertex3<float, short, Color>;
using BlockVertexBuffer = VertexBuffer<BlockVertex>;
using BlockRenderer = VertexRenderer<BlockVertex>;

struct Block {
  sourceId_t sourceId;
  modelId_t modelId;
  std::wstring displayName;
  std::wstring internalName;
};

//Class represents block stored in world
class BlockInterface {
public:

  //Default constructor
  BlockInterface() = default;

  //Default destructor
  virtual ~BlockInterface() = default;

  //
  virtual blockId_t getId() = 0;

  //
  virtual BlockVertexBuffer getVertexes() = 0;

  //
  virtual void serialize() = 0;

  //
  virtual void deserialize() = 0;
protected:

  blockId_t id_ = 0;
};
