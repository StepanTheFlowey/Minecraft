#pragma once

#include "main.hpp"

#include <atomic>
#include <thread>
#include "SettingsManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
#include "BlockManager.hpp"

struct Resource {
  std::wstring source;
  std::wstring name;
  uint16_t id;
};

class TextRenderer;
class LoadingScreen;

class Assets {
  std::thread* thread_ = nullptr;
  std::atomic_bool work_ = true;
  GLuint font = 0;
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
