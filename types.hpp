#pragma once 

#define RAPIDJSON_USE_STD_STRING true
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#define STB_ONLY_PNG 
#define STB_DEFINE 

#include <inttypes.h>
#include <cmath>
#include <string>
#include <iostream>
#include <Windows.h>

#define DEPRECATED [[deprecated("don`t use it")]]
#define NODISCARD [[nodiscard("did you left something")]]

NODISCARD __forceinline std::wstring wide(std::string str) {
  return std::wstring(str.begin(), str.end());
}

template <class E, typename T = std::underlying_type_t<E>> 
NODISCARD __forceinline T to_underlying(E enumeration) {
  return static_cast<T>(enumeration);
}