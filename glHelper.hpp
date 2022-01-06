#pragma once

#include "types.hpp"

#include <vector>
#include "glad.h"

class GlHelper {
  GLdouble aspect_ = 0;
public:
  bool vboSupport = false;
  //bool vaoSupport = false;

  std::wstring vendor;
  std::wstring renderer;
  std::wstring version;
  std::vector<std::wstring> extensions;

  void init2D(GLdouble width, GLdouble height);

  void init3D(GLdouble width, GLdouble height);

  bool isExtensionSupport(std::wstring name);

  void loadInfo();

  void loadGL();

  void clear();

  static void checkForErrors(const uint32_t line) {
    switch(glGetError()) {
      case GL_NO_ERROR:
        break;
      case GL_INVALID_ENUM:
        std::wcout << L"Line " << line << L" error GL_INVALID_ENUM" << std::endl;
        break;
      case GL_INVALID_VALUE:
        std::wcout << L"Line " << line << L" error GL_INVALID_VALUE" << std::endl;
        break;
      case GL_INVALID_OPERATION:
        std::wcout << L"Line " << line << L" error GL_INVALID_OPERATION" << std::endl;
        break;
      case GL_STACK_OVERFLOW:
        std::wcout << L"Line " << line << L" error GL_STACK_OVERFLOW" << std::endl;
        break;
      case GL_STACK_UNDERFLOW:
        std::wcout << L"Line " << line << L" error GL_STACK_UNDERFLOW" << std::endl;
        break;
      case GL_OUT_OF_MEMORY:
        std::wcout << L"Line " << line << L" error GL_OUT_OF_MEMORY" << std::endl;
        break;
    }
  }
};