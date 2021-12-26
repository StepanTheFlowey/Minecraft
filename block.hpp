#pragma once
#include "types.hpp"
#include "vec3.hpp"
#include "aabb3.hpp"
#include "plane.hpp"
#include "side.hpp"

using blockId_t = uint16_t;
using blockPos_t = int32_t;
using modelId_t = uint16_t;
using textureId_t = GLuint;

using BlockPos = Vec3<blockPos_t>;
using BlockAabb = Aabb3<blockPos_t>;
using BlockPlane = Plane<blockPos_t>;

struct BlockRenderInfo {
  blockId_t blockId = 0;
  Side side;
};

struct BlockInfo {
  uint8_t solidSides = 0b00000010;  //All, None, Up, Down, North, South, West, East
  blockId_t blockId = 0;
  blockId_t sourceId = 0;
  modelId_t blockModel = 0;
  textureId_t textureId[6] = {0,0,0,0,0,0};
  std::wstring blockSourceDisplayName = L"no_source";
  std::wstring blockDisplayName = L"No display name";
  std::wstring blockInternalName = L"no_internal_name";
  std::wstring textureName[6] = {L"none",L"none",L"none",L"none",L"none",L"none"};
};

struct BlockWithSide {
  BlockPos pos;
  Side side;
};

class BaseBlock {
public:
  blockId_t Id;
};
