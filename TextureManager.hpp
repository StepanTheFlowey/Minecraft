#pragma once

#include <map>
#include "Block.hpp"

class TextureManager {
public:

  inline TextureManager() {
    debug(L"TextureManager()");
  }

  inline ~TextureManager() {
    debug(L"~TextureManager()");
  }

  void load();

  void save();

  inline textureId_t getTextureId(const std::wstring name) {
    return textures_.at(name);
  }
protected:

  std::map<std::wstring, textureId_t> textures_;
};
