#include "Game.hpp"

#include "Player.hpp"
#include "World.hpp"
#include "GlHelper.hpp"
#include "DisplayList.hpp"
#include "DisplayHelper.hpp"

Game::Game() {
  debug(L"Game()");
}

Game::~Game() {
  debug(L"~Game()");
}

void Game::operator()() {
  World* const world = new World;
  world->makeCurrent();

  Player* const player = new Player;

  DisplayList axisList(GL_COMPILE);
  {
    constexpr float_t axisLenght = 17.F;
    constexpr float_t axisOffset = -0.1F;

    glBegin(GL_LINES);

    glColor3ub(255, 0, 0);
    glVertex3f(axisOffset, axisOffset, axisOffset);
    glVertex3f(axisLenght, axisOffset, axisOffset);

    glColor3ub(0, 255, 0);
    glVertex3f(axisOffset, axisOffset, axisOffset);
    glVertex3f(axisOffset, axisLenght, axisOffset);

    glColor3ub(0, 0, 255);
    glVertex3f(axisOffset, axisOffset, axisOffset);
    glVertex3f(axisOffset, axisOffset, axisLenght);

    glColor3ub(255, 255, 255);

    glEnd();
  }
  axisList.end();

  //Setup renderer
  gl->init3D();

  glFrontFace(GL_CCW);
  glLineWidth(3);

  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);

  display->window.setMouseCursorGrabbed(true);

  Time gametime;
  sf::Clock clock;
  while(true) {
    display->autoClock();
    while(display->pollEvent()) {
      switch(display->event.type) {
        case sf::Event::Closed:
          display->window.close();
          break;
        case sf::Event::Resized:
          display->window.setSize(sf::Vector2u(display->event.size.width, display->event.size.height));
          display->videoMode.width = display->event.size.width;
          display->videoMode.height = display->event.size.height;
          gl->init3D();
          break;
        case sf::Event::MouseMoved:
        {
          Vec2u windowSize = display->window.getSize();
          Vec2i mousePos(display->event.mouseMove.x, display->event.mouseMove.y);
          Vec2f rotation;

          rotation = windowSize / 2 - mousePos;
          rotation /= Vec2f(windowSize) * 2;
          rotation *= Vec2f(360, 180);
          sf::Mouse::setPosition(sf::Vector2i(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)), display->window);
          player->camera.rotate(rotation);
        }
        break;
        case sf::Event::MouseButtonPressed:
          switch(display->event.mouseButton.button) {
            case sf::Mouse::Left:
              player->placeBlock();
              break;
            case sf::Mouse::Right:
              player->breakBlock();
              break;
          }
          break;
        case sf::Event::KeyPressed:
          switch(display->event.key.code) {
            case sf::Keyboard::W:
              player->walk(Side::Forward, true);
              break;
            case sf::Keyboard::S:
              player->walk(Side::Back, true);
              break;
            case sf::Keyboard::A:
              player->walk(Side::Left, true);
              break;
            case sf::Keyboard::D:
              player->walk(Side::Right, true);
              break;
            case sf::Keyboard::Space:
              player->walk(Side::Up, true);
              break;
            case sf::Keyboard::LShift:
              player->walk(Side::Down, true);
              break;
            case sf::Keyboard::F11:
              display->toggleFullscreen();
              gl->init3D();
              break;
          }
          break;
        case sf::Event::KeyReleased:
          switch(display->event.key.code) {
            case sf::Keyboard::W:
              player->walk(Side::Forward, false);
              break;
            case sf::Keyboard::S:
              player->walk(Side::Back, false);
              break;
            case sf::Keyboard::A:
              player->walk(Side::Left, false);
              break;
            case sf::Keyboard::D:
              player->walk(Side::Right, false);
              break;
            case sf::Keyboard::Space:
              player->walk(Side::Up, false);
              break;
            case sf::Keyboard::LShift:
              player->walk(Side::Down, false);
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

    display->window.display();
  }

  display->window.setMouseCursorGrabbed(false);

  delete player;
  delete world;
}
