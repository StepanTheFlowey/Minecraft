#pragma once

#include "main.hpp"

class GameScreen {
public:

  inline GameScreen() {
    debug(L"GameScreen()");
  }

  inline ~GameScreen() {
    debug(L"~GameScreen()");
  }

  void operator()();
};