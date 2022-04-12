#include "TextRenderer.hpp"

#include "Assets.hpp"

float TextRenderer::size = 8.F;

void TextRenderer::drawBegin() {
  glBindTexture(GL_TEXTURE_2D, assets->font);

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

  float_t offset;
  Vec2i16 tex;
  for(size_t i = 0; i < text_.size(); ++i) {
    tex.x = text_[i] % 16;
    tex.y = text_[i] / 16;
    offset = i * size;

    glTexCoord2s(tex.x, tex.y);
    glVertex2f(0.0F + offset, 0.0F);

    glTexCoord2s(tex.x, tex.y + 1);
    glVertex2f(0.0F + offset, size);

    glTexCoord2s(tex.x + 1, tex.y + 1);
    glVertex2f(size + offset, size);

    glTexCoord2s(tex.x + 1, tex.y);
    glVertex2f(size + offset, 0.0F);
  }

  glEnd();

  list_.end();
}
