#pragma once

#include <map>
#include "Block.hpp"

class TextureManager {
public:

  TextureManager() {
    debug(L"TextureManager()");
  }

  ~TextureManager() {
    debug(L"~TextureManager()");
  }

  void load();

  void save();

  inline textureId_t getTextureId(const std::wstring name) const {
    return textures_.at(name);
  }
protected:

  std::map<std::wstring, textureId_t> textures_;
};
