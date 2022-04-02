#pragma once

#include "main.hpp"

#include <set>
#include "glad.h"

class GlHelper {
  GLdouble aspect_ = 0;
public:

  bool vaoSupport = false;
  bool vboSupport = false;
  bool shaderSupport = false;

  std::wstring vendor;
  std::wstring renderer;
  std::wstring version;
  std::set<std::wstring> extensions;

  void init2D();

  void init3D();

  bool isExtensionSupport(const std::wstring name) const;

  void loadInfo();

  void clearInfo();

  static void loadGL();

  static void initGL();

  static void checkForErrors(const char* file, const uint32_t line);
};
extern GlHelper* gl;
