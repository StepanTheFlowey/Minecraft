#pragma once

#include "main.hpp"

#include <atomic>
#include <thread>
#include "LoadingScreen.hpp"
#include "SettingsManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
#include "BlockManager.hpp"

class Assets {
  std::thread thread_;
  std::atomic_bool done_;
public:
  SettingsManager settingsManager;
  ModelManager modelManager;
  TextureManager textureManager;
  BlockManager blockManager;

  Assets();

  ~Assets();

  inline bool done() {
    return done_;
  }

private:

  void task();
};
extern Assets* assets;
