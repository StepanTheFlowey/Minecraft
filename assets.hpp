#pragma once

#include "types.hpp"
#include "block.hpp"

#include <map>
#include <filesystem>

#include <stb/stb_image.h>

#include <gl/GLU.h>
#include "glad.h"

//#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

class TextureManager {
  std::map<std::wstring, textureId_t> textures_;
public:
  TextureManager() {
#ifdef DEBUG
    std::wcout << L"TextureManager()" << std::endl;
#endif // DEBUG
  }

  ~TextureManager() {
#ifdef DEBUG
    std::wcout << L"~TextureManager()" << std::endl;
#endif // DEBUG
  }

  void load(std::wstring path = L"textures\\") {
    int width = 0;
    int height = 0;
    int comp = 0;
    uint8_t* image;
    uint32_t texture = 0;
    for(const auto& i : fs::directory_iterator(path)) {
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
    for(auto& [iKey, iVal] : textures_) {
      name = L"Name: " + iKey;
      std::wcout << name;
      for(uint8_t i = 0; i < 30 - name.length(); i++) {
        std::wcout << " ";
      }
      std::wcout << L"ID: " << iVal << std::endl;
    }
#endif // DEBUG
  }

  std::map<std::wstring, textureId_t>& getTextures() {
    //TODO: Exeption if textures_.empty()
    return textures_;
  }

  void clean() {

  }
};

class BlockManager {
public:
  static std::vector<Block*> blocks_;

  BlockManager() {
#ifdef DEBUG
    std::wcout << L"BlockManager()" << std::endl;
#endif // DEBUG
  }

  ~BlockManager() {
#ifdef DEBUG
    std::wcout << L"~BlockManager()" << std::endl;
#endif // DEBUG
  }

  void load() {

  }
};

class Assets {
public:
  TextureManager textures;
  BlockManager blocks;

  Assets() {
#ifdef DEBUG
    std::wcout << L"Assets()" << std::endl;
#endif // DEBUG
    //TODO: Dir checking
  }

  ~Assets() {
#ifdef DEBUG
    std::wcout << L"~Assets()" << std::endl;
#endif // DEBUG
  }

  void bindTextures() {
    //TODO: Assets::bindTextures()
  }
};