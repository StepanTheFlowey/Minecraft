#pragma once

#include <map>
#include <stb/stb_image.h>

class TextureManager {
  std::map<std::wstring, textureId_t> textures_;
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
};