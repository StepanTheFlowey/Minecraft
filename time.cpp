#pragma once

#include "Time.hpp"

Time::Time() {

}

Time::Time(const int64_t time) {
  time_ = time;
}

Time::Time(const Time& time) {
  time_ = time.time_;
}

Time::Time(const sf::Time& time) {
  time_ = time.asMicroseconds();
}

Time::~Time() {

}

void Time::setSeconds(const float_t seconds) {
  time_ = static_cast<int64_t>(seconds * 1000000);
}

void Time::setMilliseconds(const int32_t millis) {
  time_ = static_cast<int64_t>(millis) * 1000;
}

void Time::setMicroseconds(const int64_t micros) {
  time_ = micros;
}

float_t Time::asSeconds() const {
  return static_cast<float_t>(static_cast<double_t>(time_) / 1000000.0);
}

int32_t Time::asMilliseconds() const {
  return static_cast<int32_t>(time_ / 1000);
}

int64_t Time::asMicroseconds() const {
  return time_;
}

Time Time::seconds(const float_t seconds) {
  return Time(static_cast<int64_t>(seconds * 1000000));
}

Time Time::milliseconds(const int32_t millis) {
  return Time(static_cast<int64_t>(millis) * 1000);
}

Time Time::microseconds(const int64_t micros) {
  return Time(micros);
}
