#pragma once

#include "main.hpp"

class ModelManager {
  //std::map<std::wstring, Model> models_;
public:

  inline ModelManager() {
    debug(L"ModelManager()");
  }

  inline ~ModelManager() {
    debug(L"~ModelManager()");
  }

  void load();

  void save();
};