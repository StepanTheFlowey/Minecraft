#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include "GlHelper.hpp"
#include "DisplayHelper.hpp"

class Loading {
  std::atomic_bool work_ = true;
  std::atomic_bool loop_ = true;

  bool update_ = true;
  uint16_t all_ = 0;
  uint16_t progress_ = 0;
  std::wstring what_;
  std::mutex mutex_;

  std::thread* thread_;
public:

  Loading(const uint32_t all, const std::wstring what);

  ~Loading();

  void wait();

  void next(const std::wstring what);

  inline void done() {
    work_ = false;
  }
private:

  void task();
};
extern Loading* loading;
