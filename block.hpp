#pragma once
#include "types.hpp"

#include <string>

struct BlockRenderInfo {
  blockId_t blockId = 0;
  uint8_t sideRender = 0b00000010;  //All, None, Up, Down, North, South, West, East
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

class Block {
public:
  blockId_t Id;
};