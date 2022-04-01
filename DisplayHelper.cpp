#include "DisplayHelper.hpp"

DisplayHelper* display = nullptr;

void DisplayHelper::init() {
  window.create(videoMode, "Minecraft Alpha", sf::Style::Default, contextSettings);
  window.setVerticalSyncEnabled(true);
}