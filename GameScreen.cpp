#include "GameScreen.hpp"

#include "DisplayList.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "GlHelper.hpp"
#include "DisplayHelper.hpp"

void GameScreen::operator()() {
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
  gl->init3D();

  glFrontFace(GL_CCW);
  glLineWidth(3);
  glPointSize(10);

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
          Vec2f windowSize = display->window.getSize();
          Vec2f mousePos(display->event.mouseMove.x, display->event.mouseMove.y);
          Vec2f rotation;
          windowSize /= 2;
          rotation = windowSize - mousePos;
          rotation /= windowSize * 2;
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
            case sf::Keyboard::F11:
              display->toggleFullscreen();
              gl->init3D();
              break;
          }
          break;
        case sf::Event::KeyReleased:
          switch(display->event.key.code) {
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

    display->window.display();
  }

  display->window.setMouseCursorGrabbed(false);

  delete player;
  delete world;
}
