#pragma once

#include "main.hpp"
#include "Vec2.hpp"
#include "Color.hpp"
#include "DisplayList.hpp"

class Assets;

class TextRenderer {
  static uint8_t charWidths_[256];
  static GLuint font_;

  DisplayList list_;
  std::wstring text_;
  Vec2f position_;
  Color color_;
public:

  inline TextRenderer() :color_(255, 255, 255) {
    debug(L"TextRenderer()");
  }

  inline TextRenderer(const std::wstring text) : color_(255, 255, 255) {
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

  inline static void setFont(const GLuint font) {
    font_ = font;
  }

  static void drawBegin();

  void draw();

  static void drawEnd();
private:

  void update();

  friend Assets;
};
