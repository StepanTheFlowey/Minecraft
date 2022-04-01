#pragma once

#include <thread>
#include <mutex>
#include "GlHelper.hpp"

class LoadingScreen {
  std::thread renderThread_;
  std::mutex mutex_;
  std::atomic_bool work_;
public:

  LoadingScreen();

  ~LoadingScreen();
private:

  void task();
};