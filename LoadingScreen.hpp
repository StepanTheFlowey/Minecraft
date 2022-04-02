#pragma once

#include <thread>
#include <mutex>
#include "GlHelper.hpp"

class LoadingScreen {
  bool work_ = true;
  uint32_t progress_ = 0;
  uint32_t all_ = 0;
  std::thread renderThread_;
  std::mutex mutex_;
public:

  LoadingScreen(const uint32_t all);

  ~LoadingScreen();

  inline void next() {
    ++progress_;
  }
private:

  void task();
};
