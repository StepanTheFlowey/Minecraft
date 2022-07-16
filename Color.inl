#pragma once

constexpr Color::Color(
  const uint8_t _r,
  const uint8_t _g,
  const uint8_t _b,
  const uint8_t _a
) :
  r(_r),
  g(_g),
  b(_b),
  a(_a) {

}

void Color::glColor() const {
  glColor4ub(r, g, b, a);
}
