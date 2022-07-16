#pragma once

#include "main.hpp"

class ModelManager {
public:

  ModelManager() {
    debug(L"ModelManager()");
  }

  ~ModelManager() {
    debug(L"~ModelManager()");
  }

  void load();

  void save();
protected:

  //std::map<std::wstring, Model> models_;
};
