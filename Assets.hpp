#pragma once

#include "main.hpp"

#include <vector>
#include <atomic>
#include <thread>
#include "SettingsManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
#include "BlockManager.hpp"

struct Resource {
  std::wstring source;
  std::wstring name;
  uint16_t id = 0;
};

class TextRenderer;
class Loading;

class Assets {
public:

  SettingsManager settingsManager;
  ModelManager modelManager;
  TextureManager textureManager;
  BlockManager blockManager;

  Assets();

  ~Assets();

  void loadEarly();

  void load();
protected:

  void loadResources();

  void task();

  std::vector<Resource> resources;

  std::thread* thread_ = nullptr;

  friend SettingsManager;
  friend ModelManager;
  friend TextureManager;
  friend BlockManager;
};
extern Assets* assets;
