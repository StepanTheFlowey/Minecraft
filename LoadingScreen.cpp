#include "LoadingScreen.hpp"

#include "DisplayHelper.hpp"
#include "resource.h"
#include <stb/stb_image.h>

LoadingScreen::LoadingScreen(const uint32_t all) :renderThread_(&LoadingScreen::task, this) {
  debug(L"LoadingScreen()");
  all_ = all;
}

LoadingScreen::~LoadingScreen() {
  debug(L"~LoadingScreen()");
  work_ = false;
  renderThread_.join();
}

void LoadingScreen::task() {
  gl->init2D();

  GLuint texture = 0;
  {
    HRSRC hResource = FindResourceW(NULL, MAKEINTRESOURCEW(IDB_PNG1), L"PNG");
    if(!hResource) throw;

    HGLOBAL hMemory = LoadResource(NULL, hResource);
    if(!hMemory) throw;

    int x = 0;
    int y = 0;
    int comp = 0;
    stbi_uc* const img = stbi_load_from_memory(
      reinterpret_cast<stbi_uc*>(LockResource(hMemory)),
      SizeofResource(NULL, hResource), &x, &y, &comp, 3
    );

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    stbi_image_free(img);
  }

  float_t p = 0.0F;
  mutex_.lock();
  while(work_&& display->alive()) {
    p = 0.6F * (static_cast<float_t>(progress_) / all_);
    mutex_.unlock();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);

    glColor3ub(255, 255, 255);
    glVertex2f(-0.32F, 0.28F);
    glVertex2f(-0.32F, 0.37F);
    glVertex2f(0.32F, 0.37F);
    glVertex2f(0.32F, 0.28F);

    glColor3ub(0, 0, 0);
    glVertex2f(-0.31F, 0.27F);
    glVertex2f(-0.31F, 0.36F);
    glVertex2f(0.31F, 0.36F);
    glVertex2f(0.31F, 0.27F);

    glColor3ub(255, 255, 255);
    glVertex2f(-0.3F, 0.3F);
    glVertex2f(-0.3F, 0.35F);
    glVertex2f(-0.3F + p, 0.35F);
    glVertex2f(-0.3F + p, 0.3F);

    glEnd();

    display->window.display();
    display->autoEvent();

    mutex_.lock();
  }
  mutex_.unlock();

  glDeleteTextures(1, &texture);
}
