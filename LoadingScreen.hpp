#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include "GlHelper.hpp"

class LoadingScreen {
  std::atomic_bool work_ = true;

  bool update_ = true;
  uint16_t all_ = 0;
  uint16_t progress_ = 0;
  std::wstring what_;
  std::mutex mutex_;

  std::thread* thread_;
public:

  LoadingScreen(const uint32_t all, const std::wstring what);

  ~LoadingScreen();

  void next(const std::wstring what) {
    mutex_.lock();
    update_ = true;
    ++progress_;
    what_ = what;
    mutex_.unlock();
  }
private:

  void task();
};
extern LoadingScreen* loading;
