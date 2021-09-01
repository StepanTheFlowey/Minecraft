//Std lib
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <filesystem>
//STL containers
#include <unordered_map>
#include <bitset>
#include <vector>
#include <array>
#include <map>
#include <set>

//Stb
#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#define STB_ONLY_PNG
#include <stb/stb_image.h>

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

//OpenGL
#include <gl/GL.h>
#include <gl/GLU.h>

//RapidJSON
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson\filereadstream.h>
#include <rapidjson\filewritestream.h>
#include <rapidjson\document.h>
#include <rapidjson\writer.h>

//#include "Point.hpp"
//#include "Rect.hpp"

//Math defines
#define PI 3.1415926535897932384626433832795
#define DEG_TO_RAD 0.017453292519943295769236907684886

//Bit operation defines
#define bitRead(value, bit) (((value) >> (bit))&0x1)
#define bitSet(value, bit) ((value) |= (1 << (bit)))
#define bitClear(value, bit) ((value) &= ~(1 << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

//Data types
using gametime_t = int32_t;
using size_t = std::size_t;
using shortsize_t = uint32_t;
using shortersize_t = uint16_t;
using blockId_t = uint16_t;
using modelId_t = uint16_t;
using textureId_t = GLuint;
using regionPos_t = int16_t;
using chunkPos_t = int32_t;
using blockPos_t = int32_t;

//Namespaces
namespace fs = std::filesystem;

//Using Utils class instead of global vars
class Utils {
  std::error_code err_c_;
  char charBuff_[1024];
public:
  Utils() {
    clearCharBuff();
  }

  ~Utils() {

  }

  void clearCharBuff() {
    memset(charBuff_, 0, sizeof(charBuff_));
  }

  char *getCharBuff() {
    return charBuff_;
  }

  std::error_code &getErrorCode() {
    return err_c_;
  }

  constexpr std::size_t getCharBuffSize() {
    return sizeof(charBuff_);
  }
};

class Settings {
  bool isLoaded = false;
public:

  Settings() {

  }

  ~Settings() {

  }

  bool load(std::wstring filename = L"settings.json") {
    return false;
  }

  bool save(std::wstring filename = L"settings.json") {
    return false;
  }

  operator bool() const {
    return isLoaded;
  }
};

class TextureManager {
  std::map<std::wstring, textureId_t> textures_;
  std::set<textureId_t> usedTextures_;
public:
  TextureManager() {
#ifdef DEBUG
    std::wcout << L"TextureManager(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~TextureManager() {
#ifdef DEBUG
    std::wcout << L"~TextureManager(): Destructor" << std::endl;
#endif // DEBUG
  }

  void load(std::wstring path = L"textures\\") {
    int width = 0;
    int height = 0;
    int comp = 0;
    uint8_t *image;
    textureId_t texture = 0;
    for(const auto &i : fs::directory_iterator(path)) {
      if(!i.is_directory()) {
        char buff[1024];
        stbi_convert_wchar_to_utf8(buff, sizeof(buff), fs::canonical(i).wstring().c_str());

        image = stbi_load(buff, &width, &height, &comp, 4);
        if(image) {
          glGenTextures(1, &texture);
          glBindTexture(GL_TEXTURE_2D, texture);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
          stbi_image_free(image);
          textures_[i.path().filename().wstring()] = texture;
        }
        else {
          std::wcout << "Can`t load image \"" << i.path().filename().wstring() << "\"\nReason: " << std::endl << stbi_failure_reason() << std::endl;
        }
      }
    }

    //for(auto &[iKey, iVal] : textures_) {
    //  std::wcout << L"Name: " << iKey << L"\t\t\tID: " << iVal << std::endl;
    //}

    //_wsystem(L"pause");
  }

  std::map<std::wstring, textureId_t> &getTextures() {
    //TODO: Exeption if textures_.empty()
    return textures_;
  }

  void doNotDelete(textureId_t textureId) {
    usedTextures_.insert(textureId);
  }

  void clean() {

  }
};

struct BlockRenderInfo {
  uint8_t sideRender = 0b00000010;      //All, None, Up, Down, North, South, West, East
  blockId_t blockId = 0;
};

struct BlockInfo {
  uint8_t solidSides = 0b00000010;  //All, None, Up, Down, North, South, West, East
  blockId_t blockId = 0;
  blockId_t sourceId = 0;
  modelId_t blockModel = 0;
  textureId_t textureId[6] = {0,0,0,0,0,0};
  std::wstring blockSourceDisplayName = L"no_source";
  std::wstring blockDisplayName = L"No display name";
  std::wstring blockInternalName = L"no_internal_name";
  std::wstring textureName[6] = {L"none",L"none",L"none",L"none",L"none",L"none"};
};

class BlockManager {
  std::vector<BlockInfo> blocks_;
public:

  BlockManager() {
#ifdef DEBUG
    std::wcout << L"BlockManager(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~BlockManager() {
#ifdef DEBUG
    std::wcout << L"~BlockManager(): Destructor" << std::endl;
#endif // DEBUG
  }

  void load(std::wstring path = L"blocks\\") {

  }

  std::vector<BlockInfo> &getBlocks() {
    return blocks_;
  }
};

class Assets {
public:
  Settings *settings;
  TextureManager *textures;
  BlockManager *blocks;

  Assets() {
#ifdef DEBUG
    std::wcout << L"Assets(): Constructor" << std::endl;
#endif // DEBUG
    //TODO: Dir checking
    settings = new Settings;
    textures = new TextureManager;
    blocks = new BlockManager;
  }

  ~Assets() {
#ifdef DEBUG
    std::wcout << L"~Assets(): Destructor" << std::endl;
#endif // DEBUG
  }

  void bindTextures() {
    auto &blocksVector = blocks->getBlocks();
    auto &texturesMap = textures->getTextures();
    textureId_t txId = 0;

    for(auto &i : blocksVector) {
      for(uint8_t j = 0; j < 6; j++) {
        if(texturesMap.find(i.textureName[j]) != texturesMap.end()) {
          txId = texturesMap[i.textureName[j]];
          textures->doNotDelete(txId);
          //TODO: do this
        }
      }
    }
  }
};

class Chunk {
  std::array<std::array<std::array<BlockRenderInfo, 16>, 16>, 16> block_;
  chunkPos_t x_ = 0, y_ = 0, z_ = 0;
public:

  Chunk() {
#ifdef DEBUG
    std::wcout << L"Chunk(): Constructor" << std::endl;
#endif // DEBUG
    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          block_[i][j][k].blockId = 1;
        }
      }
    }
    block_[5][15][6].blockId = 0;
  }

  ~Chunk() {
#ifdef DEBUG
    std::wcout << L"~Chunk(): Destructor" << std::endl;
#endif // DEBUG
  }

  BlockRenderInfo &getBlockNative(uint8_t x, uint8_t y, uint8_t z) {
    return block_[x][y][z];
  }

  void setBlock(uint8_t x, uint8_t y, uint8_t z, BlockRenderInfo block) {
    block_[x][y][z] = block;
  }

  void setPosition(chunkPos_t x, chunkPos_t y, chunkPos_t z) {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  void draw() {
    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          BlockRenderInfo &block = block_[i][j][k];
          if(bitRead(block.sideRender, 1)) {
            continue;
          }
          glBindTexture(GL_TEXTURE_2D, 2);
          glPushMatrix();

          glTranslatef(i + static_cast<GLfloat>(x_) * 16, j + static_cast<GLfloat>(y_) * 16, k + static_cast<GLfloat>(z_) * 16);

          glBegin(GL_QUADS);

          glColor3ub(255, 255, 255);

          if(bitRead(block.sideRender, 0)) {
            //Up side
            glTexCoord2s(0, 0);
            glVertex3s(0, 1, 1);
            glTexCoord2s(0, 1);
            glVertex3s(1, 1, 1);
            glTexCoord2s(1, 1);
            glVertex3s(1, 1, 0);
            glTexCoord2s(1, 0);
            glVertex3s(0, 1, 0);

            //Down side
            glTexCoord2s(0, 0);
            glVertex3s(1, 0, 1);
            glTexCoord2s(1, 0);
            glVertex3s(1, 0, 0);
            glTexCoord2s(1, 1);
            glVertex3s(0, 0, 0);
            glTexCoord2s(0, 1);
            glVertex3s(0, 0, 1);

            //North side
            glTexCoord2s(0, 0);
            glVertex3s(0, 1, 0);
            glTexCoord2s(0, 1);
            glVertex3s(0, 0, 0);
            glTexCoord2s(1, 1);
            glVertex3s(0, 0, 1);
            glTexCoord2s(1, 0);
            glVertex3s(0, 1, 1);

            //South side
            glTexCoord2s(0, 0);
            glVertex3s(1, 1, 1);
            glTexCoord2s(1, 0);
            glVertex3s(1, 1, 0);
            glTexCoord2s(1, 1);
            glVertex3s(1, 0, 0);
            glTexCoord2s(0, 1);
            glVertex3s(1, 0, 1);

            //West side
            glTexCoord2s(0, 0);
            glVertex3s(0, 1, 1);
            glTexCoord2s(0, 1);
            glVertex3s(0, 0, 1);
            glTexCoord2s(1, 1);
            glVertex3s(1, 0, 1);
            glTexCoord2s(1, 0);
            glVertex3s(1, 1, 1);

            //East side
            glTexCoord2s(0, 0);
            glVertex3s(1, 1, 0);
            glTexCoord2s(0, 1);
            glVertex3s(1, 0, 0);
            glTexCoord2s(1, 1);
            glVertex3s(0, 0, 0);
            glTexCoord2s(1, 0);
            glVertex3s(0, 1, 0);
          }
          else {
            if(bitRead(block.sideRender, 2)) {
              //Up side
              glTexCoord2s(0, 0);
              glVertex3s(0, 1, 1);
              glTexCoord2s(0, 1);
              glVertex3s(1, 1, 1);
              glTexCoord2s(1, 1);
              glVertex3s(1, 1, 0);
              glTexCoord2s(1, 0);
              glVertex3s(0, 1, 0);
            }
            if(bitRead(block.sideRender, 3)) {
              //Down side
              glTexCoord2s(0, 0);
              glVertex3s(1, 0, 1);
              glTexCoord2s(0, 1);
              glVertex3s(0, 0, 1);
              glTexCoord2s(1, 1);
              glVertex3s(0, 0, 0);
              glTexCoord2s(1, 0);
              glVertex3s(1, 0, 0);
            }
            if(bitRead(block.sideRender, 4)) {
              //North side
              glTexCoord2s(0, 0);
              glVertex3s(0, 1, 0);
              glTexCoord2s(0, 1);
              glVertex3s(0, 0, 0);
              glTexCoord2s(1, 1);
              glVertex3s(0, 0, 1);
              glTexCoord2s(1, 0);
              glVertex3s(0, 1, 1);
            }
            if(bitRead(block.sideRender, 5)) {
              //South side
              glTexCoord2s(0, 0);
              glVertex3s(1, 1, 1);
              glTexCoord2s(0, 1);
              glVertex3s(1, 0, 1);
              glTexCoord2s(1, 1);
              glVertex3s(1, 0, 0);
              glTexCoord2s(1, 0);
              glVertex3s(1, 1, 0);
            }
            if(bitRead(block.sideRender, 6)) {
              //West side
              glTexCoord2s(0, 0);
              glVertex3s(0, 1, 1);
              glTexCoord2s(0, 1);
              glVertex3s(0, 0, 1);
              glTexCoord2s(1, 1);
              glVertex3s(1, 0, 1);
              glTexCoord2s(1, 0);
              glVertex3s(1, 1, 1);
            }
            if(bitRead(block.sideRender, 7)) {
              //East side
              glTexCoord2s(0, 0);
              glVertex3s(1, 1, 0);
              glTexCoord2s(0, 1);
              glVertex3s(1, 0, 0);
              glTexCoord2s(1, 1);
              glVertex3s(0, 0, 0);
              glTexCoord2s(1, 0);
              glVertex3s(0, 1, 0);
            }
          }
          glEnd();

          glPopMatrix();
        }
      }
    }
  }
};

class Region {
  std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::unordered_map<uint8_t, Chunk>>> chunk_;
  regionPos_t x_ = 0;
  regionPos_t y_ = 0;
  regionPos_t z_ = 0;
public:
  Region() {
#ifdef DEBUG
    std::wcout << L"Region(): Constructor" << std::endl;
#endif // DEBUG
    chunk_[0][0][0] = Chunk();
  }

  ~Region() {
#ifdef DEBUG
    std::wcout << L"~Region(): Destructor" << std::endl;
#endif // DEBUG
  }

  BlockRenderInfo getBlockWorld(blockPos_t x, blockPos_t y, blockPos_t z) {

  }

  BlockRenderInfo getBlockNative(blockPos_t x, blockPos_t y, blockPos_t z) {

  }

  void setPosition(regionPos_t x, regionPos_t y, regionPos_t z) {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  Chunk &getChunk(uint8_t x, uint8_t y, uint8_t z) {
    return chunk_[x][y][z];
  }

  bool hasChunk(uint8_t x, uint8_t y, uint8_t z) {
    if(chunk_.find(x) == chunk_.end()) {
      return false;
    }
    if(chunk_[x].find(y) == chunk_[x].end()) {
      return false;
    }
    if(chunk_[x][y].find(z) == chunk_[x][y].end()) {
      return false;
    }
    return true;
  }

  void draw() {
    for(auto &[iKey, iVal] : chunk_) {
      for(auto &[jKey, jVal] : iVal) {
        for(auto &[kKey, kVal] : jVal) {
          kVal.draw();
        }
      }
    }
  }
};

class World {
  std::unordered_map<regionPos_t, std::unordered_map<regionPos_t, Region>> region_;
public:
  World() {
#ifdef DEBUG
    std::wcout << L"World(): Constructor" << std::endl;
#endif // DEBUG
    region_[0][0] = Region();
    region_[0][0].setPosition(0, 0, 0);
    computeChunkEdgeRender(0, 0, 0);
  }

  ~World() {
#ifdef DEBUG
    std::wcout << L"~World(): Destructor" << std::endl;
#endif // DEBUG
  }

  bool hasRegion(regionPos_t x, regionPos_t z) {
    if(region_.find(x) == region_.end()) {
      return false;
    }
    if(region_[x].find(z) == region_[x].end()) {
      return false;
    }
    return true;
  }

  Region &getRegion(regionPos_t x, regionPos_t z) {
    return region_[x][z];
  }

  bool hasChunk(chunkPos_t x, chunkPos_t y, chunkPos_t z) {

  }

  BlockRenderInfo getBlock(blockPos_t x, blockPos_t y, blockPos_t z) {
    if(y < 0) {
      return BlockRenderInfo();
    }
    const regionPos_t rx = x / 16 / 16 + x < 0 ? 1 : 0, rz = z / 16 / 16 + z < 0 ? 1 : 0;
    if(!hasRegion(rx, rz)) {
      return BlockRenderInfo();
    }
    Region &region = region_[rx][rz];
    const chunkPos_t cx = x / 16, cy = y / 16, cz = z / 16;
    if(!region.hasChunk(cx, cy, cz)) {
      return BlockRenderInfo();
    }
    Chunk &chunk = region.getChunk(cx, cy, cz);
    return chunk.getBlockNative(x, y, z);
  }

  void setBlock(blockPos_t x, blockPos_t y, blockPos_t z, BlockRenderInfo block) {

  }

  bool computeChunkEdgeRender(chunkPos_t x, chunkPos_t y, chunkPos_t z) {
    regionPos_t rx = x / 16, rz = x / 16;
    if(!hasRegion(rx, rz)) {
      return false;
    }
    Region &region = region_[rx][rz];
    blockPos_t bx = x * 16, by = y * 16, bz = z * 16;
    x %= 16;
    z %= 16;

    if(!region.hasChunk(x, y, z)) {
      return false;
    }
    Chunk &chunk = region.getChunk(x, y, z);

    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          BlockRenderInfo &block = chunk.getBlockNative(i, j, k);
          if(block.blockId == 0) {
            bitWrite(block.sideRender, 1, 1);
            continue;
          }

          if(j == 15) {
            bitWrite(block.sideRender, 2, getBlock(bx, by + 16, bz).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 2, chunk.getBlockNative(i, j + 1, k).blockId == 0);
          }

          if(j == 0) {
            bitWrite(block.sideRender, 3, getBlock(bx, by - 1, bz).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 3, chunk.getBlockNative(i, j - 1, k).blockId == 0);
          }

          if(i == 0) {
            bitWrite(block.sideRender, 4, getBlock(bx - 1, by, bz).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 4, chunk.getBlockNative(i - 1, j, k).blockId == 0);
          }

          if(i == 15) {
            bitWrite(block.sideRender, 5, getBlock(bx + 16, by, bz).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 5, chunk.getBlockNative(i + 1, j, k).blockId == 0);
          }

          if(k == 15) {
            bitWrite(block.sideRender, 6, getBlock(bx, by, bz + 16).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 6, chunk.getBlockNative(i, j, k + 1).blockId == 0);
          }

          if(k == 0) {
            bitWrite(block.sideRender, 7, getBlock(bx, by, bz - 1).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 7, chunk.getBlockNative(i, j, k - 1).blockId == 0);
          }

          bitWrite(block.sideRender, 0, (
            bitRead(block.sideRender, 2) &&
            bitRead(block.sideRender, 3) &&
            bitRead(block.sideRender, 4) &&
            bitRead(block.sideRender, 5) &&
            bitRead(block.sideRender, 6) &&
            bitRead(block.sideRender, 7)));
          bitWrite(block.sideRender, 1, !(
            bitRead(block.sideRender, 2) ||
            bitRead(block.sideRender, 3) ||
            bitRead(block.sideRender, 4) ||
            bitRead(block.sideRender, 5) ||
            bitRead(block.sideRender, 6) ||
            bitRead(block.sideRender, 7)));
        }
      }
    }
    return true;
  }

  void draw() {
    for(auto &[iKey, iVal] : region_) {
      for(auto &[jKey, jVal] : iVal) {
        jVal.draw();
      }
    }
  }
};

class Camera {
  GLdouble x_ = 0.0, y_ = 0.0, z_ = 0.0;
  GLdouble xr_ = 0.0, yr_ = 0.0;
public:
  Camera() {
#ifdef DEBUG
    std::wcout << L"Camera(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~Camera() {
#ifdef DEBUG
    std::wcout << L"~Camera(): Destructor" << std::endl;
#endif // DEBUG
  }

  void doTranlate() {
    gluLookAt(x_, y_, z_, x_ + sin(xr_ * DEG_TO_RAD), y_ + tan(yr_ * DEG_TO_RAD), z_ + cos(xr_ * DEG_TO_RAD), 0, 1, 0);
  }

  void move(GLdouble x, GLdouble y, GLdouble z) {
    x_ += x;
    y_ += y;
    z_ += z;
  }

  void setPosition(GLdouble x, GLdouble y, GLdouble z) {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  void setRotation(GLdouble x, GLdouble y) {
    xr_ = x;
    yr_ = y;

    if(xr_ > 360) {
      xr_ = 0;
    }
    else if(xr_ < 0) {
      xr_ = 360;
    }

    if(yr_ > 90) {
      yr_ = 90;
    }
    else if(yr_ < -90) {
      yr_ = -90;
    }
  }

  void rotate(GLdouble x, GLdouble y) {
    xr_ += x;
    yr_ += y;
    if(xr_ > 360) {
      xr_ = 0;
    }
    else if(xr_ < 0) {
      xr_ = 360;
    }

    if(yr_ > 90) {
      yr_ = 90;
    }
    else if(yr_ < -90) {
      yr_ = -90;
    }
  }
};

class Player {
  bool cameraBind_ = true;                //Is camera following player eye pos and rotation
  uint8_t walkParam_ = 0;                 //Active walk dir 
  GLdouble walkSpeed_ = 0.007;            //Player walk speed
  GLdouble x_ = 0.0, y_ = 0.0, z_ = 0.0;  //Player pos
  GLdouble xr_ = 0.0, yr_ = 0.0;          //Player camera rotation
public:
  Camera camera; //Camera object

  Player() {
#ifdef DEBUG
    std::wcout << L"Player(): Constructor" << std::endl;
#endif // DEBUG
  }

  ~Player() {
#ifdef DEBUG
    std::wcout << L"~Player(): Destructor" << std::endl;
#endif // DEBUG
  }

  //Disable or enable walking in specific direction
  //TODO: replace this by func(enum or uint8_t walkDir,bool val);
  void goForward(bool val) {
    bitWrite(walkParam_, 0, val);
  }
  void goBack(bool val) {
    bitWrite(walkParam_, 1, val);
  }
  void goLeft(bool val) {
    bitWrite(walkParam_, 2, val);
  }
  void goRight(bool val) {
    bitWrite(walkParam_, 3, val);
  }
  void goUp(bool val) {
    bitWrite(walkParam_, 4, val);
  }
  void goDown(bool val) {
    bitWrite(walkParam_, 5, val);
  }

  void bindCamera() {
    cameraBind_ = true;
  }

  void unbindCamera() {
    cameraBind_ = false;
  }

  void toggleCameraBind() {
    cameraBind_ = !cameraBind_;
  }

  void move(GLdouble x, GLdouble y, GLdouble z) {
    x_ += x;
    y_ += y;
    z_ += z;
    if(cameraBind_) {
      camera.setPosition(x_, y_, z_);
    }
  }

  void update(gametime_t timeLeft) {
    //Move offset calculating: TimeAfterLastGameDisplay * WalkSpeed * other
    if(bitRead(walkParam_, 0)) {//Walk forward
      move(sin(xr_ * DEG_TO_RAD) * walkSpeed_ * timeLeft, 0, cos(xr_ * DEG_TO_RAD) * walkSpeed_ * timeLeft);
    }
    if(bitRead(walkParam_, 1)) {//Walk back
      move(sin(xr_ * DEG_TO_RAD) * walkSpeed_ * -timeLeft, 0, cos(xr_ * DEG_TO_RAD) * walkSpeed_ * -timeLeft);
    }
    if(bitRead(walkParam_, 2)) {//Walk left
      move(cos(xr_ * DEG_TO_RAD) * walkSpeed_ * timeLeft, 0, sin(xr_ * DEG_TO_RAD) * walkSpeed_ * -timeLeft);
    }
    if(bitRead(walkParam_, 3)) {//Walk r
      move(cos(xr_ * DEG_TO_RAD) * walkSpeed_ * -timeLeft, 0, sin(xr_ * DEG_TO_RAD) * walkSpeed_ * timeLeft);
    }
    if(bitRead(walkParam_, 4)) {//Walk up
      move(0, walkSpeed_ * timeLeft, 0);
    }
    if(bitRead(walkParam_, 5)) {//Walk down
      move(0, walkSpeed_ * -timeLeft, 0);
    }
    //TODO: how about realestic walk?
  }

  void setRotation(GLdouble x, GLdouble y) {
    xr_ = x;
    yr_ = y;

    if(xr_ > 360) {
      xr_ = 0;
    }
    else if(xr_ < 0) {
      xr_ = 360;
    }

    if(yr_ > 90) {
      yr_ = 90;
    }
    else if(yr_ < -90) {
      yr_ = -90;
    }

    if(cameraBind_) {
      camera.setRotation(xr_, yr_);
    }
  }

  void draw() {
    //TODO: Drawing player model
  }
};

void loadScreen() {
  //TODO: loadScreen()
}

void init2D(GLdouble width, GLdouble height) {
  //Reset projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Setup modelview matrix 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
  gluOrtho2D(0, 0, width, height);

  //Setup context
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}

void init3D(GLdouble width, GLdouble height) {
  GLdouble aspect = 0;
  if(height != 0) {
    aspect = width / height;
  }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
  gluPerspective(75, aspect, 0.1, 300);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glFrontFace(GL_CCW);
  glLineWidth(5);
  //glShadeModel(GL_SMOOTH);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_BLEND);
}

int main() {
  setlocale(LC_ALL, "Russian");

  Utils *utils=new Utils;
  Assets *assets=new Assets;
  //Bootstrap
  assets->settings->load();

  //We cannot load texture into OpenGL context without OpenGL context
  sf::Context context;
#ifdef DEBUG
  std::wcout << "Context inited" << std::endl;
#endif // DEBUG
  assets->textures->load();


  Player *player = new Player;
  World *world = new World;

  //Window init
  sf::ContextSettings contextSettings;
  contextSettings.antialiasingLevel = 0; //TODO: Enable multisampling
  contextSettings.sRgbCapable = false;   //STUPID SRGB
  contextSettings.depthBits = 24;        //what this?
  contextSettings.stencilBits = 8;       //what?
  contextSettings.majorVersion = 1;      //Request OpenGL 1.5
  contextSettings.minorVersion = 5;      //yeah
  contextSettings.attributeFlags = sf::ContextSettings::Default; //No core render please

  //Hello window
  sf::Window window(sf::VideoMode(640, 360), "Minecraft Alpha", sf::Style::Close, contextSettings);
  window.setVerticalSyncEnabled(true);
  //window.setFramerateLimit(1);

  //Setup renderer
  glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
  glClearDepth(1.0);
  init3D(640, 360);

  sf::Event event;

  bool grab = false;
  bool fullscreen = false;
  sf::Clock clock;
  gametime_t gametime = 0;
  while(window.isOpen()) {
    gametime = clock.restart().asMilliseconds();
#ifdef DEBUG
    //std::wcout << L"Time left: " << gametime << L" ms" << std::endl;
#endif // DEBUG
    while(window.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
        {
          window.close();
          break;
        }

        //TODO: Noraml window resizing
        /*case sf::Event::Resized:
        {
          window.setSize(sf::Vector2u(event.size.width, event.size.height));
          init3D(event.size.width, event.size.height);
          break;
        }*/

        case sf::Event::MouseMoved:
        {//Mouse in a trap™
          if(grab) {
            sf::Vector2u windowSize = window.getSize();
            if(event.mouseMove.x == windowSize.x - 1) {
              event.mouseMove.x = 1;
              sf::Mouse::setPosition(sf::Vector2i(0, event.mouseMove.y), window);
            }
            if(event.mouseMove.x == 0) {
              event.mouseMove.x = windowSize.x - 2;
              sf::Mouse::setPosition(sf::Vector2i(windowSize.x - 2, event.mouseMove.y), window);
            }
            event.mouseMove.x = windowSize.x - event.mouseMove.x;
            event.mouseMove.y = windowSize.y - event.mouseMove.y;
            player->setRotation((GLdouble) event.mouseMove.x / windowSize.x * 360, (GLdouble) ((GLdouble) event.mouseMove.y - windowSize.y / 2) * 2 / windowSize.y * 90);
          }
          break;
        }
        case sf::Event::KeyPressed:
        {
          switch(event.key.code) {
            case sf::Keyboard::W:
            {
              player->goForward(true);
              break;
            }
            case sf::Keyboard::S:
            {
              player->goBack(true);
              break;
            }
            case sf::Keyboard::A:
            {
              player->goLeft(true);
              break;
            }
            case sf::Keyboard::D:
            {
              player->goRight(true);
              break;
            }
            case sf::Keyboard::Space:
            {
              player->goUp(true);
              break;
            }
            case sf::Keyboard::LShift:
            {
              player->goDown(true);
              break;
            }
            case sf::Keyboard::G:
            {
              grab = !grab;
              window.setMouseCursorGrabbed(grab);
              window.setMouseCursorVisible(!grab);
              break;
            }
            case sf::Keyboard::F11:
            {
              fullscreen = !fullscreen;
              if(fullscreen) {
                sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
                window.create(videoMode, "Minecraft Alpha", sf::Style::Fullscreen, contextSettings);
                init3D(videoMode.width, videoMode.height);
              }
              else {
                window.create(sf::VideoMode(640, 360), "Minecraft Alpha", sf::Style::Close, contextSettings);
                init3D(640, 360);
              }
              if(grab) {
                window.setMouseCursorGrabbed(true);
                window.setMouseCursorVisible(false);
              }
              break;
            }
          }
          break;
        }
        case sf::Event::KeyReleased:
        {
          switch(event.key.code) {
            case sf::Keyboard::W:
            {
              player->goForward(false);
              break;
            }
            case sf::Keyboard::S:
            {
              player->goBack(false);
              break;
            }
            case sf::Keyboard::A:
            {
              player->goLeft(false);
              break;
            }
            case sf::Keyboard::D:
            {
              player->goRight(false);
              break;
            }
            case sf::Keyboard::Space:
            {
              player->goUp(false);
              break;
            }
            case sf::Keyboard::LShift:
            {
              player->goDown(false);
              break;
            }
          }
          break;
        }
      }
    }

    player->update(gametime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    player->camera.doTranlate();

    //Axis lines
    glBegin(GL_LINES);

    glColor3ub(255, 0, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(16, 0, 0);

    glColor3ub(0, 255, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 16, 0);

    glColor3ub(0, 0, 255);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 16);

    glEnd();
    world->draw();
    glPopMatrix();

    window.display();
  }

#ifdef DEBUG
  //_wsystem(L"pause");
#endif //DEBUG
}