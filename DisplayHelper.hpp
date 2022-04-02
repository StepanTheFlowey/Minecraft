#pragma once

#include "main.hpp"
#include <SFML/Window.hpp>

class DisplayHelper {
public:
  sf::VideoMode videoMode;
  sf::ContextSettings contextSettings{};
  sf::Event event{};
  sf::Window window;

  sf::Clock clock;
  sf::Time time;

  inline DisplayHelper() {
    debug(L"DisplayHelper");
    contextSettings.antialiasingLevel = 16; //Multisampling level
    contextSettings.depthBits = 32;         //Depth buffer bits
    contextSettings.majorVersion = 2;       //Request OpenGL 2.1
    contextSettings.minorVersion = 1;
  }

  inline ~DisplayHelper() {
    debug(L"~DisplayHelper");
  }

  void init();

  inline bool alive() {
    return window.isOpen();
  }

  inline void autoEvent() {
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
        exit(EXIT_SUCCESS);
      }
    }
  }

  inline void autoClock() {
    time = clock.restart();
  }

  inline bool pollEvent() {
    return window.pollEvent(event);
  }
};
extern DisplayHelper* display;