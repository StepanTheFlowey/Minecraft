#pragma once

#include "main.hpp"

class ModelManager {
public:

  inline ModelManager() {
    debug(L"ModelManager()");
  }

  inline ~ModelManager() {
    debug(L"~ModelManager()");
  }

  void load();

  void save();
protected:

  //std::map<std::wstring, Model> models_;
};
