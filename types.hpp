#pragma once 
#define WIN32_LEAN_AND_MEAN true
#include <inttypes.h>
#include <string>
#include <iostream>
#include <Windows.h>

//TODO: remove bitOp defines 
//Bit operation defines
#define bitRead(value, bit) (((value) >> (bit))&0x1)
#define bitSet(value, bit) ((value) |= (1 << (bit)))
#define bitClear(value, bit) ((value) &= ~(1 << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define DEPRECATED [[deprecated("This function is deprecated and is not recommended to use it")]]

std::wstring wide(std::string str) {
  return std::wstring(str.begin(), str.end());
}