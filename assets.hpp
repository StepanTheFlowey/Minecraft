#pragma once

#include "main.hpp"
#include "block.hpp"

#include <gl/GLU.h>
#include "glad.h"

#include "textureManager.hpp"

class BlockManager {
  std::vector<BlockInfo> blocks_;
public:

  BlockManager() {
    debug(L"BlockManager()");
  }

  ~BlockManager() {
    debug(L"~BlockManager()");
  }

  void load() {

  }
};

class ModelManager {
  //std::map<std::wstring, Model> modesl_;
public:

  ModelManager() {
    debug(L"ModelManager()");
  }

  ~ModelManager() {
    debug(L"~ModelManager()");
  }
};

class Assets {
public:
  TextureManager textureManager;
  ModelManager modelManager;
  BlockManager blockManager;

  Assets() {
    debug(L"Assets()");
  }

  ~Assets() {
    debug(L"~Assets()");
  }
};
extern Assets* assets;