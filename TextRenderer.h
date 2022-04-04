#pragma once

#include "main.hpp"

class TextRenderer {
  std::wstring text_;
public:

  inline TextRenderer() {
    debug(L"TextRenderer()");
  }

  inline TextRenderer(std::wstring text) {
    debug(L"TextRenderer()");
    text_ = text;
  }

  inline ~TextRenderer() {
    debug(L"~TextRenderer()");
  }
};

