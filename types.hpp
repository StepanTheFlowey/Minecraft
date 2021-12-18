#pragma once 
#define WIN32_LEAN_AND_MEAN true
#include <inttypes.h>
#include <string>
#include <iostream>
#include <Windows.h>

#define DEPRECATED [[deprecated("This function is deprecated and is not recommended to use it")]]

std::wstring wide(std::string str) {
  return std::wstring(str.begin(), str.end());
}

template <typename T, class E> T to_underlying(E enumeration) {
  return static_cast<std::underlying_type_t<E>>(enumeration);
}