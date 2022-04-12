#include "Assets.hpp"

#include <stb/stb_image.h>
#include "Loading.hpp"
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
  loading = new Loading(5, L"Enumerating assets");
  thread_ = new std::thread(&Assets::task, this);

  loading->wait();

  thread_->join();
  delete thread_;
  delete loading;
}

void Assets::loadResources() {
  resources.reserve(64);
}

void Assets::task() {
  loadResources();        loading->next(L"Loading block manager");
  blockManager.load();    loading->next(L"Loading model manager");
  modelManager.load();    loading->next(L"Loading texture manager");
  textureManager.load();  loading->next(L"Loading settings manager");
  settingsManager.load(); loading->next(L"Finalazing game");

  loading->done();
}
