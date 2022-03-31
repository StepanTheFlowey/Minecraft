#pragma once

#include "main.hpp"
#include "vec3.hpp"
#include "aabb3.hpp"
#include "side.hpp"
#include <vector>
#include <functional>

using blockId_t = uint16_t;
using sourceId_t = uint16_t;
using modelId_t = uint16_t;
using textureId_t = uint16_t;
using blockPos_t = int32_t;

using BlockPos = Vec3<blockPos_t>;
using BlockAabb = Aabb3<blockPos_t>;

struct BlockWithSide {
  BlockPos pos;
  Side side = Side::Null;
};

struct BlockInfo {
  static sourceId_t sourceId;
  static modelId_t modelId;
  static std::wstring displayName;
  static std::wstring internalName;
  static std::wstring tilesetName;
};

class Block {
public:
  Side side = Side::Null;
  blockId_t id = 0;
};

template <typename T> Block* createBlock() {
  throw std::logic_error("no block with such type");
}

template <> Block* createBlock<Block>() {
  return new Block;
}