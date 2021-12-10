#pragma once
#include "Time.hpp"

Time::Time() {

}

Time::~Time() {

}

void Time::setSeconds(float_t seconds) {
  time_ = static_cast<int64_t>(seconds * 1000000);
}

void Time::setMilliseconds(int32_t millis) {
  time_ = static_cast<int64_t>(millis) * 1000;
}

void Time::setMicroseconds(int64_t micros) {
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