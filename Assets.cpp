#include "Assets.hpp"

Assets* assets = nullptr;

Assets::Assets() : thread_(&Assets::task, this) {
  debug(L"Assets()");
}

Assets::~Assets() {
  debug(L"~Assets()");
  thread_.join();
}

void Assets::task() {
  loading = new LoadingScreen(4);
  _wsystem(L"pause");
  blockManager.load();    loading->next();
  _wsystem(L"pause");
  modelManager.load();    loading->next();
  _wsystem(L"pause");
  textureManager.load();  loading->next();
  _wsystem(L"pause");
  settingsManager.load(); loading->next();
  _wsystem(L"pause");
  delete loading;
  done_ = true;
}
