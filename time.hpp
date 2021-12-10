#pragma once
#include "types.hpp"

class Time {
  int64_t time_ = 0;
public:
  Time();
  ~Time();

  void setSeconds(float_t);
  void setMilliseconds(int32_t);
  void setMicroseconds(int64_t);

  float_t asSeconds() const;
  int32_t asMilliseconds() const;
  int64_t asMicroseconds() const;
};