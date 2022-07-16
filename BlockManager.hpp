#pragma once

#include <vector>
#include "main.hpp"
#include "block.hpp"

class BlockManager {
public:

  BlockManager() {
    debug(L"BlockManager()");
  }

  ~BlockManager() {
    debug(L"~BlockManager()");
  }

  void load();

  void save();
protected:

  //std::vector<BlockInfo> blocks_;

  void loadFromModule() {

  }
};
