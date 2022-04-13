#include "TextRenderer.hpp"

#include "Assets.hpp"
#include "DisplayHelper.hpp"

uint8_t TextRenderer::charWidths_[256]{};
GLuint TextRenderer::font_ = 0;

void TextRenderer::drawBegin() {
  glBindTexture(GL_TEXTURE_2D, font_);

  const GLfloat matrix[16] = {
    1.F / 16.F,       0.F , 0.F, 0.F,
    0.F       , 1.F / 16.F, 0.F, 0.F,
    0.F       ,       0.F , 1.F, 0.F,
    0.F       ,       0.F , 0.F, 1.F
  };

  glMatrixMode(GL_TEXTURE);
  glPushMatrix();
  glLoadMatrixf(matrix);
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_BLEND);
}

void TextRenderer::draw() {
  glPushMatrix();
  glTranslatef(position_.x, position_.y, 0.F);
  glScalef(display->scale, display->scale, display->scale);
  list_.call();
  glPopMatrix();
}

void TextRenderer::drawEnd() {
  glMatrixMode(GL_TEXTURE);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  glDisable(GL_BLEND);
}

void TextRenderer::update() {
  list_.begin();

  glBegin(GL_QUADS);

  color_.glColor();
  float_t offset = 0.F;
  Vec2i16 tex;
  for(size_t i = 0; i < text_.size(); ++i) {
    tex.x = text_[i] % 16;
    tex.y = text_[i] / 16;

    glTexCoord2s(tex.x, tex.y);
    glVertex2f(0.0F + offset, 0.0F);

    glTexCoord2s(tex.x, tex.y + 1);
    glVertex2f(0.0F + offset, 8);

    glTexCoord2s(tex.x + 1, tex.y + 1);
    glVertex2f(8 + offset, 8);

    glTexCoord2s(tex.x + 1, tex.y);
    glVertex2f(8 + offset, 0.F);

    offset += charWidths_[text_[i]];
  }

  glEnd();

  list_.end();
}
