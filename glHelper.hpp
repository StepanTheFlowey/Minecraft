#pragma once

#include "main.hpp"

#include <vector>
#include "glad.h"

class GlHelper {
  GLdouble aspect_ = 0;
public:
 
  bool vboSupport = false;
  bool vaoSupport = false;

  std::wstring vendor;
  std::wstring renderer;
  std::wstring version;
  std::vector<std::wstring> extensions;

  void init2D(const GLdouble width, const GLdouble height);

  void init3D(const GLdouble width, const GLdouble height);

  bool isExtensionSupport(const std::wstring name) const;

  void loadInfo();

  void clearInfo();

  static void loadGL();

  static void initGL();

  static void checkForErrors(const uint32_t line);
};