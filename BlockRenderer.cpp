#include "BlockRenderer.hpp"

#include "main.hpp"
#include "Math.hpp"
#include "Rect3.hpp"

BlockRenderer::BlockRenderer() {
  debug(L"BlockRenderer()");
  glGenBuffersARB(1, &bufferHandle_);
}

BlockRenderer::~BlockRenderer() {
  debug(L"~BlockRenderer()");
  glDeleteBuffers(1, &bufferHandle_);
}

void BlockRenderer::computeBuffer(Block** const blocks) {
  std::vector<Vertex> vertex;
  vertex.reserve(256);

  bool allSides;
  SmallPos blockPos;
  for(uint16_t i = 0; i < 4096; ++i) {
    if(blocks[i] == nullptr) {
      continue;
    }
    if(blocks[i]->id == 0) {
      continue;
    }

    blockPos.x = i % 16;
    blockPos.y = i % 256 / 16;
    blockPos.z = i / 256;

    allSides = to_underlying(blocks[i]->side & Side::All);

    if(to_underlying(blocks[i]->side & Side::Up) || allSides) {
      //Up side
      vertex.push_back(Vertex{Rect3<int16_t>::Up.a + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::Up.b + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::Up.c + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::Up.d + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
    }
    if(to_underlying(blocks[i]->side & Side::Down) || allSides) {
      //Down side
      vertex.push_back(Vertex{Rect3<int16_t>::Down.a + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::Down.b + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::Down.c + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::Down.d + blockPos,Vec2<int16_t>(0,0),Color(0,255,0)});
    }
    if(to_underlying(blocks[i]->side & Side::North) || allSides) {
      //North side
      vertex.push_back(Vertex{Rect3<int16_t>::North.a + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::North.b + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::North.c + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::North.d + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
    }
    if(to_underlying(blocks[i]->side & Side::South) || allSides) {
      //South side
      vertex.push_back(Vertex{Rect3<int16_t>::South.a + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::South.b + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::South.c + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
      vertex.push_back(Vertex{Rect3<int16_t>::South.d + blockPos,Vec2<int16_t>(0,0),Color(255,0,0)});
    }
    if(to_underlying(blocks[i]->side & Side::West) || allSides) {
      //West side
      vertex.push_back(Vertex{Rect3<int16_t>::West.a + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
      vertex.push_back(Vertex{Rect3<int16_t>::West.b + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
      vertex.push_back(Vertex{Rect3<int16_t>::West.c + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
      vertex.push_back(Vertex{Rect3<int16_t>::West.d + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
    }
    if(to_underlying(blocks[i]->side & Side::East) || allSides) {
      //East side
      vertex.push_back(Vertex{Rect3<int16_t>::East.a + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
      vertex.push_back(Vertex{Rect3<int16_t>::East.b + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
      vertex.push_back(Vertex{Rect3<int16_t>::East.c + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
      vertex.push_back(Vertex{Rect3<int16_t>::East.d + blockPos,Vec2<int16_t>(0,0),Color(0,0,255)});
    }
  }
  size_ = vertex.size();

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, bufferHandle_);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertex.size() * sizeof(Vertex), vertex.data(), GL_STREAM_DRAW_ARB);
}

void BlockRenderer::draw() const {
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, bufferHandle_);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_SHORT, 14, (void*)0);
  glTexCoordPointer(2, GL_SHORT, 14, (void*)6);
  glColorPointer(4, GL_UNSIGNED_BYTE, 14, (void*)10);

  glDrawArrays(GL_QUADS, 0, size_);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
