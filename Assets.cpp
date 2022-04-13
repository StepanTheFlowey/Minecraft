#include "Assets.hpp"

#include <stb/stb_image.h>
#include "Loading.hpp"
#include "DisplayHelper.hpp"
#include "TextRenderer.hpp"
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

  GLuint font = 0;
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &font);
  glBindTexture(GL_TEXTURE_2D, font);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
  checkGLerrors();

  TextRenderer::font_ = font;

  for(uint8_t i = 0; i < 33; ++i) {
    TextRenderer::charWidths_[i] = 0;
  }

  TextRenderer::charWidths_[32] = 5;

  Vec2u16 pos;
  for(uint8_t i = 33; i < 255; ++i) {
    pos.x = i % 16 * 8;
    pos.y = i / 16 * 8;

    uint8_t j;
    for(j = 0; j < 8; ++j) {
      uint8_t k;
      for(k = 0; k < 8; ++k) {
        if(reinterpret_cast<uint32_t*>(img)[(pos.x + j) + 128 * (pos.y + k)]) {
          break;
        }
      }
      if(k == 8) {
        break;
      }
    }
    TextRenderer::charWidths_[i] = (j == 8 ? 8 : j + 1);
  }

  stbi_image_free(img);
}

void Assets::load() {
  loading = new Loading(5, L"Loading assets");
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
