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
  GLuint font = 0;
  std::vector<Resource> resources;

  std::thread* thread_ = nullptr;
public:

  SettingsManager settingsManager;
  ModelManager modelManager;
  TextureManager textureManager;
  BlockManager blockManager;

  Assets();

  ~Assets();

  void loadEarly();

  void load();

private:

  void loadResources();

  void task();

  friend SettingsManager;
  friend ModelManager;
  friend TextureManager;
  friend BlockManager;

  friend TextRenderer;
};
extern Assets* assets;
