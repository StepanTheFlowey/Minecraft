#pragma once

#include <mutex>
#include <atomic>
#include <SFML/Window.hpp>
#include "main.hpp"

class DisplayHelper {
  std::mutex mutex_;
  std::atomic_bool fullscrEvent_ = false;
  std::atomic_bool resizeEvent_ = true;
public:
  sf::VideoMode videoMode;
  sf::ContextSettings contextSettings{};
  sf::Event event{};
  sf::Window window;

  sf::Clock clock;
  sf::Time time;

  bool fullscreen = false;
  uint8_t scale = 2;

  inline DisplayHelper() {
    debug(L"DisplayHelper");
    contextSettings.antialiasingLevel = 8;  //Multisampling level
    contextSettings.depthBits = 24;         //Depth buffer bits
    contextSettings.majorVersion = 2;       //Request OpenGL 2.1
    contextSettings.minorVersion = 1;
  }

  inline ~DisplayHelper() {
    debug(L"~DisplayHelper");
  }

  void init();

  inline bool alive() {
    std::unique_lock lock(mutex_);
    return window.isOpen();
  }

  inline void autoClock() {
    time = clock.restart();
  }

  //Automatic event handling. Needs to be called from event thread
  void autoEvent();

  //Manual event handling. Needs to be called from event thread
  bool pollEvent();

  //Renderer event handling. Needs to be called from render thread
  bool taskEvent();

  void toggleFullscreen();
};
extern DisplayHelper* display;
