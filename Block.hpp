#pragma once

#include "main.hpp"
#include "vec3.hpp"
#include "aabb3.hpp"
#include "side.hpp"
#include <vector>
#include <functional>

using blockId_t = uint16_t;   //Max 65535 blocks in one source
using sourceId_t = uint16_t;  //Max 65535 sources (e.g. mods)
using modelId_t = uint16_t;   //Max 65535 block model
using textureId_t = uint16_t; //Max 65535 textures
using blockPos_t = int32_t;   //Absolute block pos

using BlockPos = Vec3<blockPos_t>;
using BlockAabb = Aabb3<blockPos_t>;

struct BlockWithSide {
  BlockPos pos;
  Side side = Side::Null;
};

//TODO: move to assets types
struct BlockInfo {
  static sourceId_t sourceId;
  static modelId_t modelId;
  static std::wstring displayName;
  static std::wstring internalName;
  static std::wstring tilesetName;
};

//Class represents block stored in world
class Block {
public:
  Side side = Side::Null;
  blockId_t id = 0;
};

template <typename T> inline Block* createBlock() {
  throw std::logic_error("no block with such type");
}

template <> inline Block* createBlock<Block>() {
  return new Block;
}
