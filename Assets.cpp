#include "Assets.hpp"

#include <stb/stb_image.h>
#include "LoadingScreen.hpp"
#include "DisplayHelper.hpp"
#include "resource.h"

Assets* assets = nullptr;

Assets::Assets() {
  debug(L"Assets()");
}

Assets::~Assets() {
  debug(L"~Assets()");
}

void Assets::loadEarly() {
  debug(L"Assets::loadEarly()");

  HRSRC hResource = FindResourceW(NULL, MAKEINTRESOURCEW(ID_PNG2), L"PNG");
  if(!hResource) throw;

  HGLOBAL hMemory = LoadResource(NULL, hResource);
  if(!hMemory) throw;

  int x = 0;
  int y = 0;
  int comp = 0;
  stbi_uc* const img = stbi_load_from_memory(
    reinterpret_cast<stbi_uc*>(LockResource(hMemory)),
    SizeofResource(NULL, hResource), &x, &y, &comp, 4
  );

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &font);
  glBindTexture(GL_TEXTURE_2D, font);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
  checkGLerrors();
  stbi_image_free(img);
}

void Assets::load() {
  display->window.setActive(false);
  thread_ = new std::thread(&Assets::task, this);
  while(work_) {
    display->autoEvent();
    Sleep(16);
  }
  thread_->join();
  delete thread_;
}

void Assets::loadResources() {

}

void Assets::task() {
  loading = new LoadingScreen(5, L"Enumerating assets");
  _wsystem(L"pause");
  loadResources();        loading->next(L"Loading block manager");
  _wsystem(L"pause");
  blockManager.load();    loading->next(L"Loading model manager");
  _wsystem(L"pause");
  modelManager.load();    loading->next(L"Loading texture manager");
  _wsystem(L"pause");
  textureManager.load();  loading->next(L"Loading settings manager");
  _wsystem(L"pause");
  settingsManager.load(); loading->next(L"Finalazing game");
  _wsystem(L"pause");
  delete loading;
  work_ = false;
}
