#pragma once

#include <mutex>
#include <SFML/Window.hpp>
#include "main.hpp"

class DisplayHelper {
  std::mutex mutex_;
public:
  sf::VideoMode videoMode;
  sf::ContextSettings contextSettings{};
  sf::Event event{};
  sf::Window window;

  sf::Clock clock;
  sf::Time time;

  bool fullscreen = false;

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

  void autoEvent();

  bool pollEvent();

  void toggleFullscreen();
};
extern DisplayHelper* display;
