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

enum class Side :uint8_t{
  None = 1 << 0,
  All = 1 << 1,
  Up = 1 << 2,
  Down = 1 << 3,
  North = 1 << 4,
  South = 1 << 5,
  West = 1 << 6,
  East = 1 << 7
};

inline Side operator & (Side &l, Side &r) {
  using T = std::underlying_type_t <Side>;
  return static_cast<Side>(static_cast<T>(l) & static_cast<T>(r));
}

inline Side &operator &= (Side &l, Side &r) {
  l = l & r;
  return l;
}

inline Side operator | (Side &l, Side &r) {
  using T = std::underlying_type_t <Side>;
  return static_cast<Side>(static_cast<T>(l) | static_cast<T>(r));
}

inline Side &operator |= (Side &l, Side &r) {
  l = l | r;
  return l;
}

class Block {
public:
  blockId_t Id;
};