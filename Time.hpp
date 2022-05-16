#pragma once

#include <SFML\System\Time.hpp>
#include "main.hpp"

class Time {
  int64_t time_;
public:

  //Default constructor
  constexpr Time();

  //Microseconds constructor
  constexpr explicit Time(const int64_t time);

  //Copy constructor from sfml time
  constexpr Time(const sf::Time& time);

  //Default destructor
  ~Time();

  //Seconds assignment
  void setSeconds(const float_t);

  //Milliseconds assignment
  void setMilliseconds(const int32_t);

  //Microseconds assignment
  void setMicroseconds(const int64_t);

  //Seconds taking function
  float_t asSeconds() const;

  //Milliseconds taking function
  int32_t asMilliseconds() const;

  //Microseconds taking function
  int64_t asMicroseconds() const;

  //Construct a time value from a number of seconds
  static Time seconds(const float_t);

  //Construct a time value from a number of milliseconds
  static Time milliseconds(const int32_t);

  //Construct a time value from a number of microseconds
  static Time microseconds(const int64_t);

  //
  bool operator==(const Time& time);

  //
  bool operator!=(const Time& time);

  //
  Time operator+(const Time& time);
  
  //
  Time operator-(const Time& time);
  
  //
  Time operator*(const Time& time);

  //
  Time operator/(const Time& time);

  //
  Time operator%(const Time& time);

  //
  void operator+=(const Time& time);

  //
  void operator-=(const Time& time);

  //
  void operator*=(const Time& time);

  //
  void operator/=(const Time& time);

  //
  void operator%=(const Time& time);
};

#include "Time.inl"
