#pragma once

#include <set>
#include "main.hpp"
#include "glad.h"

#define checkGLerrors() GlHelper::checkForErrors(__FILE__,__LINE__)

class GlHelper {
public:

  std::wstring vendor;
  std::wstring renderer;
  std::wstring version;
  std::set<std::wstring> extensions;

  GlHelper();

  ~GlHelper();

  void init2D();

  void init3D();

  bool isExtensionSupport(const std::wstring name) const;

  void loadInfo();

  void clearInfo();

  static void loadGL();

  static void initGL();

  static void checkForErrors(const char* file, const uint32_t line);
protected:

  GLdouble aspect_ = 0;
};
extern GlHelper* gl;
