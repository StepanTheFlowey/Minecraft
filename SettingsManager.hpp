#pragma once

#include "main.hpp"

enum class Bool : bool {
  False = 0,
  True
};

enum class RendererType : uint8_t {
  Shader = 0,
  Vbo,
  Vao,
  Immediate
};

enum class AntialiasingLevel : uint8_t {
  Disable = 0,
  x1,
  x2,
  x4,
  x8,
  x16
};

template <typename T, T maxValue, T defaultValue>
class EnumSetting {
  T value_;
public:

  inline EnumSetting() {
    debug("EnumSetting()");
  }

  inline ~EnumSetting() {
    debug("~EnumSetting()");
  }

  const T getValue() const {
    return value_;
  }

  inline void setValue(const T value) {
    value_ = value;
  }

  inline void nextValue() {
    static_cast<int>(value_)++;
    if(value_ == maxValue) {
      value_ = static_cast<T>(0);
    }
  }

  inline const T getDefaultValue() const {
    return defaultValue;
  }

  inline void restoreDefaultValue() {
    value_ = defaultValue;
  }
};

template <typename T, T minValue, T maxValue, T defaultValue>
class RangeSetting {
  T value_;
public:

  inline RangeSetting() {
    debug("RangeSetting()");
  }

  inline ~RangeSetting() {
    debug("~RangeSetting()");
  }

  inline const T getValue() const {
    return value_;
  }

  inline void setValue(const T value) {
    value_ = value;
  }

  inline const T getMaxValue() const {
    return maxValue;
  }

  inline const T getMinValue() const {
    return minValue;
  }

  inline const T getDefaultValue() const {
    return defaultValue;
  }

  inline void restoreDefaultValue() {
    value_ = defaultValue;
  }
};

using PercentSetting = RangeSetting<uint8_t, 0, 100, 100>;
using BoolSetting = EnumSetting<Bool, Bool::True, Bool::False>;

struct Settings {
  PercentSetting                     musicVolume;
  PercentSetting                     soundVolume;
  BoolSetting                        mouseInversion;
  PercentSetting                     mouseSensevity;
  RangeSetting<uint8_t, 70, 110, 70> viewAngle;
  RangeSetting<uint8_t, 2, 64, 8>    chunkDrawDistance;
  RangeSetting<uint8_t, 2, 64, 8>    entityDrawDistance;
  PercentSetting                     brightness;
  EnumSetting<AntialiasingLevel, AntialiasingLevel::x16, AntialiasingLevel::Disable> antialiasingLevel;
};

class SettingsManager {

public:

  inline SettingsManager() {
    debug(L"SettingsManager");
  }

  inline ~SettingsManager() {
    debug(L"~SettingsManager");
  }

  void load();

  void save();
};
