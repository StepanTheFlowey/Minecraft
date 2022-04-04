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

  _wsystem(L"pause");
  assets = new Assets;
  while(!assets->done()) {
    display->autoEvent();
    sf::sleep(sf::milliseconds(16));
  }

  MenuScreen menu;

  delete assets;
  delete display;
  delete gl;

  _wsystem(L"pause");

  return 0;
}
