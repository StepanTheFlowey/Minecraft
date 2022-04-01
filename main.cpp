#include "main.hpp"

#include "Assets.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "GlHelper.hpp"
#include "DisplayHelper.hpp"
#include "DisplayList.hpp"
#include "LoadingScreen.hpp"
#include <SFML/Graphics.hpp>

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

  LoadingScreen loadingScreen;

  assets = new Assets;
  assets->blockManager.load();
  assets->modelManager.load();
  assets->textureManager.load();
  assets->settingsManager.load();

  World* const world = new World;
  world->makeCurrent();

  Player* const player = new Player;

#define AXIS_LENGHT 17.0F
#define AXIS_OFFSET -0.1F
  DisplayList axisList(GL_COMPILE);
  glBegin(GL_LINES);

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

  glEnd();
  axisList.end();
#undef AXIS_LENGHT
#undef AXIS_OFFSET

  //Setup renderer
  gl->initGL();
  gl->init3D();

  glFrontFace(GL_CCW);
  glLineWidth(3);
  glPointSize(10);

  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);

  bool grab = false;
  bool fullscreen = false;
  Time gametime;
  sf::Clock clock;
  while(window.isOpen()) {
    gametime = clock.restart();
    while(window.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::Resized:
          event.size.width -= event.size.width % 2;
          event.size.height -= event.size.height % 2;
          window.setSize(sf::Vector2u(event.size.width, event.size.height));
          gl->init3D(event.size.width, event.size.height);
          break;
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
        }
        break;
        case sf::Event::MouseButtonPressed:
          switch(event.mouseButton.button) {
            case sf::Mouse::Left:
              player->placeBlock();
              break;
            case sf::Mouse::Right:
              player->breakBlock();
              break;
          }
          break;
        case sf::Event::KeyPressed:
          switch(event.key.code) {
            case sf::Keyboard::W:
              player->setMoveDirection(Side::Forward, true);
              break;
            case sf::Keyboard::S:
              player->setMoveDirection(Side::Back, true);
              break;
            case sf::Keyboard::A:
              player->setMoveDirection(Side::Left, true);
              break;
            case sf::Keyboard::D:
              player->setMoveDirection(Side::Right, true);
              break;
            case sf::Keyboard::Space:
              player->setMoveDirection(Side::Up, true);
              break;
            case sf::Keyboard::LShift:
              player->setMoveDirection(Side::Down, true);
              break;
            case sf::Keyboard::G:
              grab = !grab;
              window.setMouseCursorGrabbed(grab);
              window.setMouseCursorVisible(!grab);
              break;
            case sf::Keyboard::F11:
            {
              fullscreen = !fullscreen;
              if(fullscreen) {
                sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
                window.create(videoMode, "Minecraft Alpha", sf::Style::Fullscreen, contextSettings);
                gl->init3D(videoMode.width, videoMode.height);
              }
              else {
                window.create(sf::VideoMode(800, 600), "Minecraft Alpha", sf::Style::Default, contextSettings);
                gl->init3D(800, 600);
              }
              if(grab) {
                window.setMouseCursorGrabbed(true);
                window.setMouseCursorVisible(false);
              }
              break;
            }
          }
          break;
        case sf::Event::KeyReleased:
          switch(event.key.code) {
            case sf::Keyboard::W:
              player->setMoveDirection(Side::Forward, false);
              break;
            case sf::Keyboard::S:
              player->setMoveDirection(Side::Back, false);
              break;
            case sf::Keyboard::A:
              player->setMoveDirection(Side::Left, false);
              break;
            case sf::Keyboard::D:
              player->setMoveDirection(Side::Right, false);
              break;
            case sf::Keyboard::Space:
              player->setMoveDirection(Side::Up, false);
              break;
            case sf::Keyboard::LShift:
              player->setMoveDirection(Side::Down, false);
              break;
          }
          break;
      }
    }

    player->update(gametime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    player->camera.doTranlate();

    world->draw();
    player->draw();

    axisList.call();

    glPopMatrix();

    //TODO: cursor
    //glBegin(GL_QUADS);

    //glVertex2f();

    //glEnd();

    window.display();
  }

  delete assets;
  delete player;
  delete world;

  delete display;
  delete gl;

  //_wsystem(L"pause");

  return 0;
}