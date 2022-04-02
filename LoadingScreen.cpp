#include "LoadingScreen.hpp"

#include "resource.h"

LoadingScreen::LoadingScreen() :renderThread_(&LoadingScreen::task, this) {
  debug(L"LoadingScreen()");
}

LoadingScreen::~LoadingScreen() {
  debug(L"~LoadingScreen()");
  work_ = false;
  renderThread_.join();
}

void LoadingScreen::task() {
  
  gl->init2D();
}
