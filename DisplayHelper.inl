#pragma once

inline DisplayHelper::DisplayHelper() {
  debug(L"DisplayHelper()");
  contextSettings.antialiasingLevel = 8;  //Multisampling level
  contextSettings.depthBits = 24;         //Depth buffer bits
  contextSettings.majorVersion = 2;       //Request OpenGL 2.1
  contextSettings.minorVersion = 1;
}

inline DisplayHelper::~DisplayHelper() {
  debug(L"~DisplayHelper()");
}

inline bool DisplayHelper::isAlive() {
  std::unique_lock lock(mutex_);
  return window.isOpen();
}

inline void DisplayHelper::autoClock() {
  time = clock.restart();
}
