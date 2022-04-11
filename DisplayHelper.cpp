#include "DisplayHelper.hpp"

DisplayHelper* display = nullptr;

void DisplayHelper::init() {
  window.create(videoMode, "Minecraft Alpha", sf::Style::Default, contextSettings);
  window.setVerticalSyncEnabled(true);
}

void DisplayHelper::autoEvent() {
  if(window.pollEvent(event)) {
    if(sf::Event::Closed == event.type) {
      window.close();
      exit(EXIT_SUCCESS);
    }
  }
}

bool DisplayHelper::pollEvent() {
  if(window.pollEvent(event)) {
    if(sf::Event::Closed == event.type) {
      window.close();
      exit(EXIT_SUCCESS);
    }
    else {
      return true;
    }
  }
  return false;
}

void DisplayHelper::toggleFullscreen() {
  fullscreen = !fullscreen;
  if(fullscreen) {
    videoMode = sf::VideoMode::getDesktopMode();
    window.create(videoMode, "Minecraft Alpha", sf::Style::Fullscreen, contextSettings);
  }
  else {
    videoMode = sf::VideoMode(800, 600);
    window.create(videoMode, "Minecraft Alpha", sf::Style::Default, contextSettings);
  }
}
