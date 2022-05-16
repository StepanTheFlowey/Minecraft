#pragma once

#include "main.hpp"

class Game {
public:

  inline Game() {
    debug(L"Game()");
  }

  inline ~Game() {
    debug(L"~Game()");
  }

  void operator()();
};
