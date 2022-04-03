#include "main.hpp"

#include "Assets.hpp"
#include "GlHelper.hpp"
#include "DisplayHelper.hpp"
#include "LoadingScreen.hpp"
#include "MenuScreen.hpp"
#include "GameScreen.hpp"

#ifdef DEBUG
int main() {
  SetConsoleTitleW(L"Minecraft Alpha Log");
#else 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
#endif // DEBUG

  sf::Context context;

  GlHelper::loadGL();

  display = new DisplayHelper;
  display->videoMode = sf::VideoMode(800, 600);
  display->init();

  gl = new GlHelper;
  gl->loadInfo();
  gl->initGL();

  display->window.setActive(false);

  LoadingScreen* loading = new LoadingScreen(5);

  _wsystem(L"pause");
  assets = new Assets;            loading->next();
  _wsystem(L"pause");
  assets->blockManager.load();    loading->next();
  _wsystem(L"pause");
  assets->modelManager.load();    loading->next();
  _wsystem(L"pause");
  assets->textureManager.load();  loading->next();
  _wsystem(L"pause");
  assets->settingsManager.load(); loading->next();

  MenuScreen menu;
  _wsystem(L"pause");
  delete loading;

  delete assets;
  delete display;
  delete gl;

  _wsystem(L"pause");

  return 0;
}
