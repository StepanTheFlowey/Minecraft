#include "main.hpp"

#include "Assets.hpp"
#include "GlHelper.hpp"
#include "DisplayHelper.hpp"
#include "LoadingScreen.hpp"
#include "MenuScreen.hpp"
#include "GameScreen.hpp"

NODISCARD __forceinline std::wstring wide(const std::string str) {
  return std::wstring(str.begin(), str.end());
}

NODISCARD __forceinline std::string shrink(const std::wstring wstr) {
  return std::string(wstr.begin(), wstr.end());
}

#ifdef DEBUG
int main() {
  SetConsoleTitleW(L"Minecraft Alpha Log");
#else 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
#endif // DEBUG

  GlHelper::loadGL();

  display = new DisplayHelper;
  display->videoMode = sf::VideoMode(800, 600);
  display->init();

  gl = new GlHelper;
  gl->loadInfo();
  gl->initGL();

  LoadingScreen* loading = new LoadingScreen;

  assets = new Assets;            loading->next();
  assets->blockManager.load();    loading->next();
  assets->modelManager.load();    loading->next();
  assets->textureManager.load();  loading->next();
  assets->settingsManager.load(); loading->next();

  delete loading;

  MenuScreen menu;

  delete assets;
  delete display;
  delete gl;

  //_wsystem(L"pause");

  return 0;
}
