#include "main.hpp"

#include <assert.h>
#include "Assets.hpp"
#include "GlHelper.hpp"
#include "DisplayHelper.hpp"
#include "Loading.hpp"
#include "Menu.hpp"
#include "Game.hpp"

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

  //_wsystem(L"pause");
  assets = new Assets;
  assets->loadEarly();
  assets->load();

  delete assets;
  delete display;
  delete gl;

  //_wsystem(L"pause");

  return EXIT_SUCCESS;
}
