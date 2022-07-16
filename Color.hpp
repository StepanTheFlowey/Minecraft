#pragma once

#include <inttypes.h>
#include "glad.h"

class Color {
public:

  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t a = 255;

  //Default constructor
  constexpr Color() = default;

  //Component constructor
  constexpr Color(
    const uint8_t r,
    const uint8_t g,
    const uint8_t b,
    const uint8_t a = 255
  );

  //Default destructor
  ~Color() = default;

  //Calls glColor(r,g,b,a)
  void glColor() const;
};

#include "Color.inl"
