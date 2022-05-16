#pragma once

#include <vector>
#include "main.hpp"
#include "block.hpp"

class BlockManager {
public:

  inline BlockManager() {
    debug(L"BlockManager()");
  }

  inline ~BlockManager() {
    debug(L"~BlockManager()");
  }

  void load();

  void save();
protected:

  std::vector<BlockInfo> blocks_;

  void loadFromModule() {

  }
};
