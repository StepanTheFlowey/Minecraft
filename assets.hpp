#pragma once

#include "main.hpp"

#include "SettingsManager.hpp"
#include "TextureManager.hpp"
#include "ModelManager.hpp"
#include "BlockManager.hpp"

class Assets {
public:
  SettingsManager settingsManager;
  TextureManager textureManager;
  ModelManager modelManager;
  BlockManager blockManager;

  inline Assets() {
    debug(L"Assets()");
  }

  inline ~Assets() {
    debug(L"~Assets()");
  }
};
extern Assets* assets;