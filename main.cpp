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

#include "aabb.hpp"
#include "vec.hpp"
#include "plane.hpp"
#include "rayTrace.hpp"
#include "color.hpp"
#include "types.hpp"
#include "math.hpp"

//Math defines
#define PI 3.1415926535897932384626433832795
#define DEG_TO_RAD 0.017453292519943295769236907684886

//Bit operation defines
#define bitRead(value, bit) (((value) >> (bit))&0x1)
#define bitSet(value, bit) ((value) |= (1 << (bit)))
#define bitClear(value, bit) ((value) &= ~(1 << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define DEPRECATED [[deprecated("This function is deprecated and is not recommended to use it")]]

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
#ifdef DEBUG
        else {
          std::wcout << "Can`t load image \"" << i.path().filename().wstring() << "\"\nReason: " << std::endl << stbi_failure_reason() << std::endl;
        }
#endif // DEBUG
      }
    }

#ifdef DEBUG
    std::wcout << L"Textures loaded:" << std::endl;
    std::wstring name;
    for(auto &[iKey, iVal] : textures_) {
      name = L"Name: " + iKey;
      std::wcout << name;
      for(uint8_t i = 0; i < 30 - name.length(); i++) {
        std::wcout << " ";
      }
      std::wcout << L"ID: " << iVal << std::endl;
    }
#endif // DEBUG
  }

  std::map<std::wstring, textureId_t> &getTextures() {
    //TODO: Exeption if textures_.empty()
    return textures_;
  }

  void clean() {

  }
};

struct BlockRenderInfo {
  blockId_t blockId = 0;
  uint8_t sideRender = 0b00000010;      //All, None, Up, Down, North, South, West, East
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
  Utils *utils_ = nullptr;
public:
  Settings *settings = nullptr;
  TextureManager *textures = nullptr;
  BlockManager *blocks = nullptr;

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
    delete settings;
    delete textures;
    delete blocks;
  }

  void setUtils(Utils *utils) {
    utils_ = utils;
  }

  void bindTextures() {
    //TODO: Assets::bindTextures()
  }
};

class Chunk {
  std::array<std::array<std::array<BlockRenderInfo, 16>, 16>, 16> block_;
  ChunkAabb aabb_;
  ChunkPos position_;
public:

  Chunk() {
#ifdef DEBUG
    std::wcout << L"Chunk(): Constructor" << std::endl;
#endif // DEBUG
    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          block_[i][j][k].blockId = rand() % 25 < 2 ? rand() % 15 : 0;
        }
      }
    }
  }

  ~Chunk() {
#ifdef DEBUG
    std::wcout << L"~Chunk(): Destructor" << std::endl;
#endif // DEBUG
  }

  BlockRenderInfo &getBlockWorld(BlockPos position) {
    position %= 16;
    return block_[position.x][position.y][position.z];
  }

  BlockRenderInfo &getBlockNative(BlockPos position) {
    return block_[position.x][position.y][position.z];
  }

  void setBlock(BlockPos position, BlockRenderInfo block) {
    block_[position.x][position.y][position.z] = block;
  }

  void setPosition(ChunkPos position) {
    position_ = position;
    aabb_.minX = position_.x;
    aabb_.minY = position_.y;
    aabb_.minZ = position_.z;
    aabb_.maxX = position_.x + 16;
    aabb_.maxY = position_.y + 16;
    aabb_.maxZ = position_.z + 16;
  }

  ChunkPos &getPosition() {
    return position_;
  }

  ChunkAabb &getAabb() {
    return aabb_;
  }

  std::array<std::array<std::array<BlockRenderInfo, 16>, 16>, 16> &getData() {
    return block_;
  }

  void draw() {
    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          BlockRenderInfo &block = block_[i][j][k];
          if(bitRead(block.sideRender, 1)) {
            continue;
          }
          glBindTexture(GL_TEXTURE_2D, block.blockId);
          glPushMatrix();

          glTranslatef(i + static_cast<GLfloat>(position_.x) * 16, j + static_cast<GLfloat>(position_.y) * 16, k + static_cast<GLfloat>(position_.z) * 16);

          glBegin(GL_QUADS);

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
            glTexCoord2s(0, 1);
            glVertex3s(0, 0, 1);
            glTexCoord2s(1, 1);
            glVertex3s(0, 0, 0);
            glTexCoord2s(1, 0);
            glVertex3s(1, 0, 0);

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
            glTexCoord2s(0, 1);
            glVertex3s(1, 0, 1);
            glTexCoord2s(1, 1);
            glVertex3s(1, 0, 0);
            glTexCoord2s(1, 0);
            glVertex3s(1, 1, 0);

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
    aabb_.drawAxisf();
  }
};

class Region {
  std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::shared_ptr<Chunk>>>> chunk_;
  RegionAabb aabb_;
  RegionPos position_;
public:
  Region() {
#ifdef DEBUG
    std::wcout << L"Region(): Constructor" << std::endl;
#endif // DEBUG
    chunk_[0][0][0].reset(new Chunk);
    chunk_[0][0][0]->setPosition(ChunkPos(0, 0, 0));
  }

  ~Region() {
#ifdef DEBUG
    std::wcout << L"~Region(): Destructor" << std::endl;
#endif // DEBUG
  }

  bool hasChunk(ChunkPos position) {
    if(chunk_.find(position.x) == chunk_.end()) {
      return false;
    }
    if(chunk_[position.x].find(position.y) == chunk_[position.x].end()) {
      return false;
    }
    if(chunk_[position.x][position.y].find(position.z) == chunk_[position.x][position.y].end()) {
      return false;
    }
    return true;
  }

  std::shared_ptr<Chunk> getChunkWorld(ChunkPos position) {
    position %= 16;
    return chunk_[position.x][position.y][position.z];
  }

  std::shared_ptr<Chunk> getChunkNative(ChunkPos position) {
    return chunk_[position.x][position.y][position.z];
  }

  BlockRenderInfo getBlockWorld(BlockPos position) {
    //TODO: Region::getBlockWorld()
  }

  BlockRenderInfo getBlockNative(BlockPos position) {
    //TODO: Region::getBlockNative()
  }

  void setPosition(RegionPos position) {
    position_ = position;
    aabb_.minX = position.x;
    aabb_.minY = 0;
    aabb_.minZ = position.y;
    aabb_.maxX = position.x + 16;
    aabb_.maxY = 256;
    aabb_.maxZ = position.y + 16;
  }

  RegionPos &getPosition() {
    return position_;
  }

  RegionAabb &getAabb() {
    return aabb_;
  }

  std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::shared_ptr<Chunk>>>> &getData() {
    return chunk_;
  }

  void draw() {
    for(auto &[iKey, iVal] : chunk_) {
      for(auto &[jKey, jVal] : iVal) {
        for(auto &[kKey, kVal] : jVal) {
          kVal->draw();
        }
      }
    }
  }
};

class World {
  std::unordered_map<regionPos_t, std::unordered_map<regionPos_t, std::shared_ptr<Region>>> region_;
public:
  World() {
#ifdef DEBUG
    std::wcout << L"World(): Constructor" << std::endl;
#endif // DEBUG
    region_[0][0].reset(new Region);
    region_[0][0]->setPosition(RegionPos(0, 0));
    computeChunkEdgeRender(ChunkPos(0, 0, 0));
  }

  ~World() {
#ifdef DEBUG
    std::wcout << L"~World(): Destructor" << std::endl;
#endif // DEBUG
  }

  bool hasRegion(RegionPos position) {
    if(region_.find(position.x) == region_.end()) {
      return false;
    }
    if(region_[position.x].find(position.y) == region_[position.x].end()) {
      return false;
    }
    return true;
  }

  std::shared_ptr<Region> getRegion(RegionPos position) {
    return region_[position.x][position.y];
  }

  bool hasChunk(ChunkPos position) {
    //TODO: Chunk::hasChunk()
  }

  std::shared_ptr<Chunk> getChunk() {
    //TODO: Chunk::getChunk()
  }

  bool hasBlock() {
    //TODO: Chunk::hasBlock()
  }

  BlockRenderInfo getBlock(BlockPos position) {
    if(position.y < 0) {
      return BlockRenderInfo {0};
    }
    RegionPos regionPosition(position.x / 256, position.z / 256);
    regionPosition.x -= position.x < 0 ? 1 : 0;
    regionPosition.y -= position.y < 0 ? 1 : 0;
    if(!hasRegion(regionPosition)) {
      return BlockRenderInfo {0};
    }
    std::shared_ptr<Region> region = region_[regionPosition.x][regionPosition.y];
    ChunkPos chunkPos = position / 16;
    chunkPos.x -= position.x < 0 ? 1 : 0;
    chunkPos.y -= position.y < 0 ? 1 : 0;
    chunkPos.z -= position.z < 0 ? 1 : 0;
    if(!region->hasChunk(chunkPos)) {
      return BlockRenderInfo {0};
    }
    BlockPos blockPos = position % 16;
    if(position.x / 16 != 0) {
      blockPos.x++;
    }
    if(position.y / 16 != 0) {
      blockPos.y++;
    }
    if(position.z / 16 != 0) {
      blockPos.z++;
    }
    return region->getChunkNative(chunkPos)->getBlockNative(blockPos);
  }

  void setBlock(BlockPos position, BlockRenderInfo block) {
    //TODO: World::setBlock()
  }

  void computeChunkEdgeRender(ChunkPos position) {
    RegionPos regionPos(position.x / 16, position.z / 16);
    if(!hasRegion(regionPos)) {
      throw std::out_of_range("no such region");
    }
    std::shared_ptr<Region> region = region_[regionPos.x][regionPos.y];
    BlockPos blockPos = position * 16;
    //position %= 16;

    if(!region->hasChunk(position)) {
      throw std::out_of_range("no such chunk");
    }
    std::shared_ptr<Chunk> chunk = region->getChunkNative(position);

    for(uint8_t i = 0; i < 16; i++) {
      for(uint8_t j = 0; j < 16; j++) {
        for(uint8_t k = 0; k < 16; k++) {
          BlockRenderInfo &block = chunk->getBlockNative(BlockPos(i, j, k));
          if(block.blockId == 0) {
            bitWrite(block.sideRender, 1, 1);
            continue;
          }

          if(j == 15) {
            bitWrite(block.sideRender, 2, getBlock(BlockPos(blockPos.x, blockPos.y + 16, blockPos.z)).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 2, chunk->getBlockNative(BlockPos(i, j + 1, k)).blockId == 0);
          }

          if(j == 0) {
            bitWrite(block.sideRender, 3, getBlock(BlockPos(blockPos.x, blockPos.y - 1, blockPos.z)).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 3, chunk->getBlockNative(BlockPos(i, j - 1, k)).blockId == 0);
          }

          if(i == 0) {
            bitWrite(block.sideRender, 4, getBlock(BlockPos(blockPos.x - 1, blockPos.y, blockPos.z)).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 4, chunk->getBlockNative(BlockPos(i - 1, j, k)).blockId == 0);
          }

          if(i == 15) {
            bitWrite(block.sideRender, 5, getBlock(BlockPos(blockPos.x + 16, blockPos.y, blockPos.z)).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 5, chunk->getBlockNative(BlockPos(i + 1, j, k)).blockId == 0);
          }

          if(k == 15) {
            bitWrite(block.sideRender, 6, getBlock(BlockPos(blockPos.x, blockPos.y, blockPos.z + 16)).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 6, chunk->getBlockNative(BlockPos(i, j, k + 1)).blockId == 0);
          }

          if(k == 0) {
            bitWrite(block.sideRender, 7, getBlock(BlockPos(blockPos.x, blockPos.y, blockPos.z - 1)).blockId == 0);
          }
          else {
            bitWrite(block.sideRender, 7, chunk->getBlockNative(BlockPos(i, j, k - 1)).blockId == 0);
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
  }

  constexpr std::unordered_map<regionPos_t, std::unordered_map<regionPos_t, std::shared_ptr<Region>>> &getData() {
    return region_;
  }

  void draw() {
    for(auto &[iKey, iVal] : region_) {
      for(auto &[jKey, jVal] : iVal) {
        jVal->draw();
      }
    }
  }
};

class Camera {
  Vec3d eyePos_;
  Vec3d centerPos_;
  Vec2d rotation_;
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
    gluLookAt(eyePos_.x, eyePos_.y, eyePos_.z, centerPos_.x, centerPos_.y, centerPos_.z, 0.0, 1.0, 0.0);
  }

  void setPosition(Vec3d position) {
    eyePos_ = position;
    process();
  }

  void setRotation(Vec2d rotation) {
    rotation_ = rotation;
    process();
  }

  void move(Vec3d offset) {
    eyePos_ += offset;
    process();
  }

  void rotate(Vec2d rotation) {
    rotation_ += rotation;
    process();
  }

  constexpr Vec2d &getRotation() {
    return rotation_;
  }

  constexpr Vec3d &getEyePosition() {
    return eyePos_;
  }

  constexpr Vec3d &getCenterPosition() {
    return centerPos_;
  }
private:
  void process() {
    if(rotation_.x > 360) {
      rotation_.x = 0;
    }
    if(rotation_.x < 0) {
      rotation_.x = 360;
    }
    if(rotation_.y > 89.99) {
      rotation_.y = 89.99;
    }
    if(rotation_.y < -89.99) {
      rotation_.y = -89.99;
    }
    centerPos_.x = eyePos_.x + sin(rotation_.x * DEG_TO_RAD) * cos(rotation_.y * DEG_TO_RAD) * 3;
    centerPos_.y = eyePos_.y + sin(rotation_.y * DEG_TO_RAD) * 3;
    centerPos_.z = eyePos_.z + cos(rotation_.x * DEG_TO_RAD) * cos(rotation_.y * DEG_TO_RAD) * 3;
  }
};

class Player {
  bool cameraBind_ = true;                //Is camera following player eye pos and rotation
  uint8_t walkParam_ = 0;                 //Active walk dir 
  GLdouble walkSpeed_ = 0.007;            //Player walk speed
  Vec3d position_;
  World *world_ = nullptr;                //World in
  BlockPos blockMouseOver_;
  std::vector<BlockPos> inters;
public:
  Camera camera; //Camera object
  bool o = false;

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
  //TODO: replace this by func(enum or uint8_t walkDir, bool val);
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

  void setWorld(World *world) {
    world_ = world;
  }
  /*
  void setUtils(Utils *utils) {
    utils_ = utils;
  }*/

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
    position_ += Vec3d(x, y, z);
    if(cameraBind_) {
      camera.setPosition(position_);
    }
  }

  void update(gametime_t timeLeft) {
    //Move offset calculating: TimeAfterLastGameDisplay * WalkSpeed * other
    Vec2d &rotation = camera.getRotation();
    if(bitRead(walkParam_, 0)) {//Walk forward
      move(sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft, 0, cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft);
    }
    if(bitRead(walkParam_, 1)) {//Walk back
      move(sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft, 0, cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft);
    }
    if(bitRead(walkParam_, 2)) {//Walk left
      move(cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft, 0, sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft);
    }
    if(bitRead(walkParam_, 3)) {//Walk r
      move(cos(rotation.x * DEG_TO_RAD) * walkSpeed_ * -timeLeft, 0, sin(rotation.x * DEG_TO_RAD) * walkSpeed_ * timeLeft);
    }
    if(bitRead(walkParam_, 4)) {//Walk up
      move(0, walkSpeed_ * timeLeft, 0);
    }
    if(bitRead(walkParam_, 5)) {//Walk down
      move(0, walkSpeed_ * -timeLeft, 0);
    }
    //TODO: how about realestic walk?
    if(o) {
      return;
    }
    Vec3d eyePos = camera.getEyePosition();
    Vec3d viewPos = camera.getCenterPosition();
    //std::wcout << "eyePos  X: " << eyePos.x << " Y: " << eyePos.y << " Z: " << eyePos.z << std::endl;
    //std::wcout << "viewPos X: " << viewPos.x << " Y: " << viewPos.y << " Z: " << viewPos.z << std::endl;
    Aabb<GLdouble> lineAABB(eyePos, viewPos);
    RayTraced rayTrace;
    BlockPlane plane;
    inters.clear();
    for(auto &[iKey, iVal] : world_->getData()) {
      for(auto &[jKey, jVal] : iVal) {
        if(jVal->getAabb().intersects(lineAABB)) {
          for(auto &[kKey, kVal] : jVal->getData()) {
            for(auto &[lKey, lVal] : kVal) {
              for(auto &[mKey, mVal] : lVal) {
                if(mVal->getAabb().intersects(lineAABB)) {
                  //std::wcout << L"chunk\n";
                  for(uint8_t i = 0; i < 16; i++) {
                    for(uint8_t j = 0; j < 16; j++) {
                      for(uint8_t k = 0; k < 16; k++) {
                        if(mVal->getBlockNative(BlockPos(i, j, k)).blockId == 0) {
                          continue;
                        }
                        plane.x = i;
                        plane.y = j;
                        plane.z = k;
                        plane.vX = 1;
                        plane.vY = 0;
                        plane.vZ = 1;
                        rayTrace.planeLineCollision(plane, eyePos, viewPos);
                        if(rayTrace.getHit()) {
                          inters.push_back(BlockPos(i, j, k));
                          continue;

                        }/*
                        plane.x = i;
                        plane.y = j + 1;
                        plane.z = k;
                        plane.vX = 1;
                        plane.vY = 0;
                        plane.vZ = 1;
                        rayTrace.planeLineCollision(plane, eyePos, viewPos);
                        if(rayTrace.getHit()) {
                          inters.push_back(BlockPos(i, j, k));
                          continue;
                        }
                        plane.x = i;
                        plane.y = j;
                        plane.z = k;
                        plane.vX = 1;
                        plane.vY = 1;
                        plane.vZ = 0;
                        rayTrace.planeLineCollision(plane, eyePos, viewPos);
                        if(rayTrace.getHit()) {
                          inters.push_back(BlockPos(i, j, k));
                          continue;
                        }
                        plane.x = i;
                        plane.y = j;
                        plane.z = k + 1;
                        plane.vX = 1;
                        plane.vY = 1;
                        plane.vZ = 0;
                        rayTrace.planeLineCollision(plane, eyePos, viewPos);
                        if(rayTrace.getHit()) {
                          inters.push_back(BlockPos(i, j, k));
                          continue;
                        }
                        plane.x = i;
                        plane.y = j;
                        plane.z = k;
                        plane.vX = 0;
                        plane.vY = 1;
                        plane.vZ = 1;
                        rayTrace.planeLineCollision(plane, eyePos, viewPos);
                        if(rayTrace.getHit()) {
                          inters.push_back(BlockPos(i, j, k));
                          continue;
                        }
                        plane.x = i + 1;
                        plane.y = j;
                        plane.z = k;
                        plane.vX = 0;
                        plane.vY = 1;
                        plane.vZ = 1;
                        rayTrace.planeLineCollision(plane, eyePos, viewPos);
                        if(rayTrace.getHit()) {
                          inters.push_back(BlockPos(i, j, k));
                          continue;
                        }*/
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    //std::wcout << inters.size() << std::endl;
    int16_t smallerNum = -1;
    for(uint16_t i = 0; i < inters.size(); i++) {
      bool smaller = true;
      //std::wcout << inters[i].distanceTo(eyePos)<<std::endl;
      for(uint16_t j = 0; j < inters.size(); j++) {
        if(i == j) {
          continue;
        }
        smaller = smaller && inters[i].distanceTo(eyePos) < inters[j].distanceTo(eyePos);
      }
      if(smaller) {
        smallerNum = i;
      }
    }
    if(smallerNum == -1) {
      blockMouseOver_ = BlockPos(-1, -1, -1);
    }
    else {
      blockMouseOver_ = inters[smallerNum];
      //std::wcout << world_->getBlock(inters[smallerNum]).blockId << std::endl;
    }
  }

  void draw() {
    //TODO: Drawing player model

    Vec3d pos(blockMouseOver_);
    BlockAabb(pos, pos + Vec3d(1, 1, 1)).drawColorf(Color(0,255,0));
#ifdef DEBUG
      glBegin(GL_LINES);

    glColor3ub(255, 0, 0);
    glVertex3d(pos.x + 3, pos.y + 0.5, pos.z + 0.5);
    glVertex3d(pos.x - 2.5, pos.y + 0.5, pos.z + 0.5);

    glColor3ub(0, 255, 0);
    glVertex3d(pos.x + 0.5, pos.y + 3, pos.z + 0.5);
    glVertex3d(pos.x + 0.5, pos.y - 2.5, pos.z + 0.5);

    glColor3ub(0, 0, 255);
    glVertex3d(pos.x + 0.5, pos.y + 0.5, pos.z + 3);
    glVertex3d(pos.x + 0.5, pos.y + 0.5, pos.z - 2.5);

    glEnd();
#endif // DEBUG
  }
};

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
  gluPerspective(60, aspect, 0.05, 200);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glFrontFace(GL_CCW);
  glLineWidth(3);
  //glShadeModel(GL_SMOOTH);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_BLEND);
}

int main() {
  setlocale(LC_ALL, "Russian");
#ifdef DEBUG
  std::wcout << L"Building main" << std::endl;
#else
  FreeConsole();
#endif //DEBUG
  Utils *utils = new Utils;
  Assets *assets = new Assets;
  World *world = new World;
  Player *player = new Player;
  player->setWorld(world);
  assets->settings->load();

  //We cannot load texture into OpenGL context without OpenGL context
  sf::Context context;
#ifdef DEBUG
  std::wcout << "Context inited" << std::endl;
#endif //DEBUG
  assets->textures->load();

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
  sf::Window window(sf::VideoMode(640, 360), "Minecraft Alpha", sf::Style::Default, contextSettings);
#ifdef DEBUG
  window.setFramerateLimit(15);
#else
  window.setVerticalSyncEnabled(true);
#endif // DEBUG

  //Setup renderer
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClearDepth(1.0);
  init3D(640, 360);

  sf::Event event;

  bool grab = false;
  bool fullscreen = false;
  gametime_t gametime = 0;
  sf::Clock clock;
  while(window.isOpen()) {
    gametime = clock.restart().asMilliseconds();
    while(window.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
        {
          window.close();
          break;
        }

        case sf::Event::Resized:
        {
          event.size.width -= event.size.width % 2;
          event.size.height -= event.size.height % 2;
          window.setSize(sf::Vector2u(event.size.width, event.size.height));
          init3D(event.size.width, event.size.height);
          break;
        }

        case sf::Event::MouseMoved:
        {//Mouse in a trap™
          if(grab) {
            Vec2f windowSize = window.getSize();
            Vec2f mousePos = sf::Mouse::getPosition(window);
            Vec2f rotation;
            windowSize /= 2;
            rotation = windowSize - mousePos;
            rotation /= windowSize * 2;
            rotation *= Vec2f(360, 180);
            sf::Mouse::setPosition(sf::Vector2i(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)), window);
            player->camera.rotate(rotation);
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
            case sf::Keyboard::O:
            {
              player->o = !player->o;
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
                window.create(sf::VideoMode(640, 360), "Minecraft Alpha", sf::Style::Default, contextSettings);
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

    world->draw();
    player->draw();

    glBegin(GL_LINES);
#define AXIS_LENGHT 17.0F
#define AXIS_OFFSET -0.1F
    glColor3ub(255, 0, 0);
    glVertex3f(AXIS_OFFSET, AXIS_OFFSET, AXIS_OFFSET);
    glVertex3f(AXIS_LENGHT, AXIS_OFFSET, AXIS_OFFSET);

    glColor3ub(0, 255, 0);
    glVertex3f(AXIS_OFFSET, AXIS_OFFSET, AXIS_OFFSET);
    glVertex3f(AXIS_OFFSET, AXIS_LENGHT, AXIS_OFFSET);

    glColor3ub(0, 0, 255);
    glVertex3f(AXIS_OFFSET, AXIS_OFFSET, AXIS_OFFSET);
    glVertex3f(AXIS_OFFSET, AXIS_OFFSET, AXIS_LENGHT);
    glColor3ub(255, 255, 255);
#undef AXIS_LENGHT
#undef AXIS_OFFSET
    glEnd();

    glPopMatrix();

    window.display();
  }
}