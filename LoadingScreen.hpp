#pragma once

#include <thread>
#include <mutex>
#include "glHelper.hpp"

class LoadingScreen {
  std::thread renderThread_;
  std::mutex mutex_;
  std::atomic_bool work_;
public:

  LoadingScreen() :renderThread_(&LoadingScreen::task, this) {

  }

  ~LoadingScreen() {

  }

private:

  void task() {

  }
};