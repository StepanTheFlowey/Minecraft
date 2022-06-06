#pragma once

#include "main.hpp"

class FontManager {
public:

  FontManager() {
    debug(L"FontManager()");
  }

  ~FontManager() {
    debug(L"~FontManager()");
  }

  void load();
};
