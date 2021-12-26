#pragma once

#include "types.hpp"

#include <SFML\System\Time.hpp>

class Time {
  int64_t time_ = 0;
public:
  
  //Default constructor
  Time();

  //Constructor from sfml time
  Time(const sf::Time&);

  //Default destructor
  ~Time();

  //Seconds assignment
  void setSeconds(float_t);

  //Milliseconds assignment
  void setMilliseconds(int32_t);

  //Microseconds assignment
  void setMicroseconds(int64_t);

  //Seconds taking function
  float_t asSeconds() const;

  //Milliseconds taking function
  int32_t asMilliseconds() const;

  //Microseconds taking function
  int64_t asMicroseconds() const;
};