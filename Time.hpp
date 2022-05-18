#pragma once

#include <SFML\System\Time.hpp>
#include "main.hpp"

class Time {
  int64_t time_ = 0;
public:

  //Default constructor
  constexpr Time();

  //Microseconds constructor
  constexpr explicit Time(const int64_t time);

  //Copy constructor from sfml time
  Time(const sf::Time& time);

  //Seconds assignment
  constexpr void setSeconds(const float_t);

  //Milliseconds assignment
  constexpr void setMilliseconds(const int32_t);

  //Microseconds assignment
  constexpr void setMicroseconds(const int64_t);

  //Seconds taking function
  constexpr float_t asSeconds() const;

  //Milliseconds taking function
  constexpr int32_t asMilliseconds() const;

  //Microseconds taking function
  constexpr int64_t asMicroseconds() const;

  //Construct a time value from a number of seconds
  constexpr static Time seconds(const float_t);

  //Construct a time value from a number of milliseconds
  constexpr static Time milliseconds(const int32_t);

  //Construct a time value from a number of microseconds
  constexpr static Time microseconds(const int64_t);

  //Equals operator
  constexpr bool operator==(const Time& time);

  //Not equals operator
  constexpr bool operator!=(const Time& time);

  //Add operator
  constexpr Time operator+(const Time& time);

  //Substract operator
  constexpr Time operator-(const Time& time);

  //
  constexpr Time operator*(const Time& time);

  //
  constexpr Time operator/(const Time& time);

  //
  constexpr Time operator%(const Time& time);

  //
  constexpr void operator+=(const Time& time);

  //
  constexpr void operator-=(const Time& time);

  //
  constexpr void operator*=(const Time& time);

  //
  constexpr void operator/=(const Time& time);

  //
  constexpr void operator%=(const Time& time);
};

#include "Time.inl"
