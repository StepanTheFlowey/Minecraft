#include "LoadingScreen.hpp"

#include <gl/GLU.h>
#include <stb/stb_image.h>
#include "DisplayHelper.hpp"
#include "resource.h"
#include "Time.hpp"

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
  display->window.setActive(true);
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
      SizeofResource(NULL, hResource), &x, &y, &comp, 4
    );

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    checkGLerrors();
    stbi_image_free(img);
  }

  glMatrixMode(GL_TEXTURE);
  gluOrtho2D(0.0, 451.0 * 2, 0.0, 49.0 * 2);
  glMatrixMode(GL_MODELVIEW);

  bool talk = false;
  bool showBar = false;
  uint8_t anim = 0;
  float_t p = 0.0F;
  sf::Time time;
  while(display->alive()) {
    time += display->clock.restart();
    p = -0.7F + 1.4F * (static_cast<float_t>(progress_) / all_);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    if(showBar) {
      glColor3ub(255, 255, 255);
      glVertex2f(-0.72F, 0.28F);
      glVertex2f(-0.72F, 0.37F);
      glVertex2f(0.72F, 0.37F);
      glVertex2f(0.72F, 0.28F);

      glColor3ub(0, 0, 0);
      glVertex2f(-0.71F, 0.29F);
      glVertex2f(-0.71F, 0.36F);
      glVertex2f(0.71F, 0.36F);
      glVertex2f(0.71F, 0.29F);

      glColor3ub(255, 255, 255);
      glVertex2f(-0.7F, 0.3F);
      glVertex2f(-0.7F, 0.35F);
      glVertex2f(p, 0.35F);
      glVertex2f(p, 0.3F);
    }

    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2s(41 * anim, 0);
    glVertex2f(-41.0F / 210.0F, -49.0F / 210.0F);
    glTexCoord2s(41 * anim, 49);
    glVertex2f(-41.0F / 210.0F, 49.0F / 210.0F);
    glTexCoord2s(41 * anim + 41, 49);
    glVertex2f(41.0F / 210.0F, 49.0F / 210.0F);
    glTexCoord2s(41 * anim + 41, 0);
    glVertex2f(41.0F / 210.0F, -49.0F / 210.0F);

    glEnd();

    if(time.asMilliseconds() > (talk ? 250 : 75)) {
      time = sf::milliseconds(0);
      if(work_) {
        ++anim;
        if(anim == 11) {
          anim = 9;
          talk = true;
          showBar = true;
        }
      }
      else {
        showBar = false;
        talk = false;
        --anim;
        if(anim == UINT8_MAX) break;
      }
    }

    display->window.display();
    display->autoEvent();
  }

  glDeleteTextures(1, &texture);

  display->window.setActive(false);
}
