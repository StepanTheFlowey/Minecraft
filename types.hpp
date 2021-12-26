#pragma once 
#define WIN32_LEAN_AND_MEAN true
#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#define STB_ONLY_PNG
#define NOMINMAX

#include <inttypes.h>
#include <cmath>
#include <string>
#include <iostream>
#include <Windows.h>

#define DEPRECATED [[deprecated("This function is deprecated and is not recommended to use it")]]

inline std::wstring wide(std::string str) {
  return std::wstring(str.begin(), str.end());
}

template <class E, typename T = std::underlying_type_t<E>> T to_underlying(E enumeration) {
  return static_cast<T>(enumeration);
}