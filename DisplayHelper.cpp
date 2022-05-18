#include "DisplayHelper.hpp"

#include "GlHelper.hpp"

DisplayHelper* display = nullptr;

void DisplayHelper::initialize() {
  window.create(videoMode, "Minecraft Alpha", sf::Style::Default, contextSettings);
  window.setVerticalSyncEnabled(true);
}

void DisplayHelper::autoEvent() {
  if(window.pollEvent(event)) {
    switch(event.type) {
      case sf::Event::Closed:
        fullscrEvent_ = true;
        while(fullscrEvent_) Sleep(1);
        window.setActive(true);
        window.close();
        exit(EXIT_SUCCESS);
      case sf::Event::Resized:
        videoMode.width = event.size.width;
        videoMode.height = event.size.height;
        resizeEvent_ = true;
        break;
      case sf::Event::KeyPressed:
        if(sf::Keyboard::F11 == event.key.code) {
          fullscrEvent_ = true;
          while(fullscrEvent_) Sleep(1);
          toggleFullscreen();
          fullscrEvent_ = true;
        }
        break;
    }
  }
}

bool DisplayHelper::pollEvent() {
  if(window.pollEvent(event)) {
    switch(event.type) {
      case sf::Event::Closed:
        fullscrEvent_ = true;
        while(fullscrEvent_) Sleep(1);
        window.setActive(true);
        window.close();
        exit(EXIT_SUCCESS);
      case sf::Event::Resized:
        videoMode.width = event.size.width;
        videoMode.height = event.size.height;
        resizeEvent_ = true;
        break;
      case sf::Event::KeyPressed:
        if(sf::Keyboard::F11 == event.key.code) {
          fullscrEvent_ = true;
          while(fullscrEvent_) Sleep(1);
          toggleFullscreen();
          fullscrEvent_ = true;
        }
        break;
    }
    return true;
  }
  return false;
}

bool DisplayHelper::taskEvent() {
  if(resizeEvent_) {
    resizeEvent_ = false;
    gl->init2D();
  }
  if(fullscrEvent_) {
    window.setActive(false);
    fullscrEvent_ = false;
    while(!fullscrEvent_) Sleep(1);
    window.setActive(true);
    gl->init2D();
    fullscrEvent_ = false;
    return true;
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
