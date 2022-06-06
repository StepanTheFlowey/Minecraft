#include "Loading.hpp"

#include <gl/GLU.h>
#include <stb/stb_image.h>
#include "DisplayHelper.hpp"
#include "TextRenderer.hpp"
#include "resource.h"

Loading* loading = nullptr;

Loading::Loading(const uint32_t all, const std::wstring what) {
  debug(L"Loading()");
  what_ = what;
  all_ = all;
  display->window.setActive(false);
  thread_ = new std::thread(&Loading::task, this);
}

Loading::~Loading() {
  debug(L"~Loading()");
  work_ = false;
  thread_->join();
  delete thread_;
  display->window.setActive(true);
}

void Loading::wait() {
  while(loop_) {
    display->autoEvent();
    Sleep(16);
  }
}

void Loading::next(const std::wstring what) {
  _wsystem(L"pause");
  mutex_.lock();
  update_ = true;
  ++progress_;
  what_ = what;
  mutex_.unlock();
}

void Loading::task() {
  display->window.setActive(true);
  gl->init2D();

  GLuint texture = 0;
  {
    HRSRC hResource = FindResourceW(NULL, MAKEINTRESOURCEW(ID_PNG1), L"PNG");
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

    const GLfloat matrix[16] = {
      1.F / x, 0.F    , 0.F, 0.F,
      0.F    , 1.F / y, 0.F, 0.F,
      0.F    , 0.F    , 1.F, 0.F,
      0.F    , 0.F    , 0.F, 1.F
    };

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

    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_TEXTURE);
    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
  }

  const float scale = display->scale;

  TextRenderer text;
  text.setPosition(Vec2f(-150.F * scale, 150.F + 12 * scale));

  const Vec2f rect0b(
    -41.F * scale,
    -49.F * scale
  );
  const Vec2f rect0e(
    41.F * scale,
    49.F * scale
  );
  const Vec2f rect1b(
    -150.F * scale,
    150.F
  );
  const Vec2f rect1e(
    150.F * scale,
    150.F + 10 * scale
  );
  const Vec2f rect2b(
    -149.F * scale,
    150.F + scale
  );
  const Vec2f rect2e(
    149.F * scale,
    150.F + 9 * scale
  );
  Vec2f rect3b(
    -148.F * scale,
    150.F + 2 * scale
  );
  Vec2f rect3e(
    148.F * scale,
    150.F + 8 * scale
  );

  bool talk = false;
  bool showBar = false;
  uint8_t anim = 0;

  sf::Time time;
  while(loop_) {
    time += display->clock.restart();

    mutex_.lock();
    if(update_) {
      update_ = false;
      rect3e.x = -148.F * scale + 296.F * scale * (static_cast<float_t>(progress_) / all_);
      text.setString(what_);
    }
    mutex_.unlock();

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
        if(anim == UINT8_MAX) {
          loop_ = false;
          break;
        }
      }
    }

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);

    glTexCoord2s(41 * anim, 0);
    glVertex2f(rect0b.x, rect0b.y);
    glTexCoord2s(41 * anim, 49);
    glVertex2f(rect0b.x, rect0e.y);
    glTexCoord2s(41 * anim + 41, 49);
    glVertex2f(rect0e.x, rect0e.y);
    glTexCoord2s(41 * anim + 41, 0);
    glVertex2f(rect0e.x, rect0b.y);

    glEnd();

    if(showBar) {
      glDisable(GL_TEXTURE_2D);

      glColor3ub(255, 255, 255);
      glRectf(rect1b.x, rect1b.y, rect1e.x, rect1e.y);

      glColor3ub(0, 0, 0);
      glRectf(rect2b.x, rect2b.y, rect2e.x, rect2e.y);

      glColor3ub(255, 255, 255);
      glRectf(rect3b.x, rect3b.y, rect3e.x, rect3e.y);

      glEnable(GL_TEXTURE_2D);

      text.drawBegin();
      text.draw();
      text.drawEnd();

      glBindTexture(GL_TEXTURE_2D, texture);
    }

    display->window.display();

    display->taskEvent();
  }

  glDeleteTextures(1, &texture);

  display->window.setActive(false);
}
