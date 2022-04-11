#include "TextRenderer.hpp"

#include "Assets.hpp"

float TextRenderer::size = 1.F / 16.F;

void TextRenderer::draw() {
  glPushMatrix();
  glTranslatef(position_.x, position_.y, 0.F);
  list_.call();
  glPopMatrix();
}

void TextRenderer::update() {
  list_.begin();

  glBindTexture(GL_TEXTURE_2D, assets->font);

  const GLfloat matrix[16] = {
    1.F / 16.F,       0.F , 0.F, 0.F,
    0.F       , 1.F / 16.F, 0.F, 0.F,
    0.F       ,       0.F , 1.F, 0.F,
    0.F       ,       0.F , 0.F, 1.F
  };

  glMatrixMode(GL_TEXTURE);
  glLoadMatrixf(matrix);
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_BLEND);
  glBegin(GL_QUADS);

  float_t offset;
  Vec2f tex;
  for(size_t i = 0; i < text_.size(); ++i) {
    tex.x = text_[i] % 16;
    tex.y = text_[i] / 16;
    offset = i * size;

    glTexCoord2f(tex.x, tex.y);
    glVertex2f(0.0F + offset, 0.0F);

    glTexCoord2f(tex.x, tex.y + 1);
    glVertex2f(0.0F + offset, size);

    glTexCoord2f(tex.x + 1, tex.y + 1);
    glVertex2f(size + offset, size);

    glTexCoord2f(tex.x + 1, tex.y);
    glVertex2f(size + offset, 0.0F);
  }

  glEnd();
  glDisable(GL_BLEND);

  list_.end();
}
