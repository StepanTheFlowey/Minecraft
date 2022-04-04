#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include "GlHelper.hpp"

class LoadingScreen {
  std::atomic_bool work_ = true;
  std::atomic_uint32_t progress_ = 0;
  std::atomic_uint32_t all_ = 0;
  std::thread thread_;
public:

  LoadingScreen(const uint32_t all);

  ~LoadingScreen();

  inline void next() {
    ++progress_;
  }
private:

  void task();
};
extern LoadingScreen* loading;
