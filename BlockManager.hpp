#pragma once

#include <vector>
#include "main.hpp"
#include "block.hpp"

class BlockManager {
  std::vector<BlockInfo> blocks_;
public:

  inline BlockManager() {
    debug(L"BlockManager()");
  }

  inline ~BlockManager() {
    debug(L"~BlockManager()");
  }

  void load();

  void save();
};
