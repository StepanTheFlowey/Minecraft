#pragma once

#include "main.hpp"
#include "Vec2.hpp"
#include "Color.hpp"
#include "DisplayList.hpp"

class TextRenderer {
  std::wstring text_;
  Vec2f position_;
  Color color_;
  DisplayList list_;
public:

  static float size;

  inline TextRenderer() {
    debug(L"TextRenderer()");
  }

  inline TextRenderer(const std::wstring text) {
    debug(L"TextRenderer(text)");
    text_ = text;
  }

  inline ~TextRenderer() {
    debug(L"~TextRenderer()");
  }

  inline const std::wstring getString() const {
    return text_;
  }

  inline void setString(const std::wstring text) {
    text_ = text;
    update();
  }

  inline Vec2f getPosition() const {
    return position_;
  }

  inline void setPosition(const Vec2f position) {
    position_ = position;
  }

  inline Color getColor() const {
    return color_;
  }

  inline void setColor(const Color color) {
    color_ = color;
    update();
  }

  static void drawBegin();

  void draw();

  static void drawEnd();
private:

  void update();
};
