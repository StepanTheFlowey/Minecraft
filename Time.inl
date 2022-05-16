#pragma once

constexpr Time::Time() {

}

constexpr Time::Time(const int64_t time) {
  time_ = time;
}

Time::Time(const sf::Time& time) {
  time_ = time.asMicroseconds();
}

constexpr void Time::setSeconds(const float_t seconds) {
  time_ = static_cast<int64_t>(seconds * 1000000);
}

constexpr void Time::setMilliseconds(const int32_t millis) {
  time_ = static_cast<int64_t>(millis) * 1000;
}

constexpr void Time::setMicroseconds(const int64_t micros) {
  time_ = micros;
}

constexpr float_t Time::asSeconds() const {
  return static_cast<float_t>(static_cast<double_t>(time_) / 1000000.0);
}

constexpr int32_t Time::asMilliseconds() const {
  return static_cast<int32_t>(time_ / 1000);
}

constexpr int64_t Time::asMicroseconds() const {
  return time_;
}

constexpr Time Time::seconds(const float_t seconds) {
  return Time(static_cast<int64_t>(seconds * 1000000));
}

constexpr Time Time::milliseconds(const int32_t millis) {
  return Time(static_cast<int64_t>(millis) * 1000);
}

constexpr Time Time::microseconds(const int64_t micros) {
  return Time(micros);
}

constexpr bool Time::operator==(const Time& time) {
  return time_ == time.time_;
}

constexpr bool Time::operator!=(const Time& time) {
  return time_ != time.time_;
}

constexpr Time Time::operator+(const Time& time) {
  return Time(time_ + time.time_);
}

constexpr Time Time::operator-(const Time& time) {
  return Time(time_ - time.time_);
}

constexpr Time Time::operator*(const Time& time) {
  return Time(time_ * time.time_);
}

constexpr Time Time::operator/(const Time& time) {
  return Time(time_ / time.time_);
}

constexpr Time Time::operator%(const Time& time) {
  return Time(time_ % time.time_);
}

constexpr void Time::operator+=(const Time& time) {
  time_ += time.time_;
}

constexpr void Time::operator-=(const Time& time) {
  time_ -= time.time_;
}

constexpr void Time::operator*=(const Time& time) {
  time_ *= time.time_;
}

constexpr void Time::operator/=(const Time& time) {
  time_ /= time.time_;
}

constexpr void Time::operator%=(const Time& time) {
  time_ %= time.time_;
}
