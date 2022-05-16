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
  float scale = 1.F;

  //Default constructor
  inline DisplayHelper();

  //Default destructor
  inline ~DisplayHelper();

  //Initializes display
  void initialize();

  //Check is display workd
  inline bool isAlive();

  //Automatic clock update
  inline void autoClock();

  //Automatic event handling. Needs to be called from event thread
  void autoEvent();

  //Manual event handling. Needs to be called from event thread
  bool pollEvent();

  //Renderer event handling. Needs to be called from render thread
  bool taskEvent();

  //Toggles fullscreen mode. Uses for F11 handle
  void toggleFullscreen();
};
extern DisplayHelper* display;

#include "DisplayHelper.inl"
