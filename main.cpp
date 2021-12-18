#include "assets.hpp"
#include "world.hpp"
#include "player.hpp"
#include "glHelper.hpp"
#include "displayList.hpp"

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

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
  gluPerspective(60, aspect, 0.05, 200);

  glFrontFace(GL_CCW);
  glLineWidth(3);
  //glShadeModel(GL_SMOOTH);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_BLEND);
}

int main() {
  //TODO: we can be not a russian
  setlocale(LC_ALL, "Russian");
#ifdef DEBUG //Object sizes for debug
  std::wcout << L"Minecraft Alpha Log" << std::endl;
  std::wcout << L"sizeof(World):\t" << sizeof(World) << std::endl;
  std::wcout << L"sizeof(Region):\t" << sizeof(Region) << std::endl;
  std::wcout << L"sizeof(Chunk):\t" << sizeof(Chunk) << std::endl;
  std::wcout << L"sizeof(BRI):\t" << sizeof(BlockRenderInfo) << std::endl;
  std::wcout << L"sizeof(Player):\t" << sizeof(Player) << std::endl;
  std::wcout << L"sizeof(Camera):\t" << sizeof(Camera) << std::endl;
#else
  FreeConsole();
#endif //DEBUG
  std::shared_ptr<Assets> assets(new Assets);
  std::shared_ptr<World> world(new World);
  world->test();

  std::shared_ptr<Player> player(new Player);
  player->setWorldIn(world);

  //Creating context without window
  sf::Context context;

  std::shared_ptr<GlHelper> glHelper(new GlHelper);
  glHelper->loadInfo();
  glHelper->loadExtensions();

  assets->textures->load();

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

  //Window init
  sf::ContextSettings contextSettings;
  contextSettings.antialiasingLevel = 0; //TODO: Enable multisampling
  contextSettings.sRgbCapable = false;   //STUPID SRGB
  contextSettings.depthBits = 24;        //Depth buffer bits
  contextSettings.stencilBits = 0;       //Stencil buffer bits
  contextSettings.majorVersion = 1;      //Request OpenGL 1.5
  contextSettings.minorVersion = 5;      //yeah
  contextSettings.attributeFlags = sf::ContextSettings::Default; //No core render please

  //Hello window
  sf::Window window(sf::VideoMode(640, 360), "Minecraft Alpha", sf::Style::Default, contextSettings);
  //#ifdef DEBUG
    //window.setFramerateLimit(15);
  //#else
  window.setVerticalSyncEnabled(true);
  //#endif // DEBUG

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
          window.close();
          break;
        case sf::Event::Resized:
          event.size.width -= event.size.width % 2;
          event.size.height -= event.size.height % 2;
          window.setSize(sf::Vector2u(event.size.width, event.size.height));
          init3D(event.size.width, event.size.height);
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
          break;
        }
        case sf::Event::MouseButtonPressed:
        {
          switch(event.mouseButton.button) {
            case sf::Mouse::Left:
              player->placeBlock();
              break;
            case sf::Mouse::Right:
              player->breakBlock();
              break;
          }
          break;
        }
        case sf::Event::KeyPressed:
        {
          switch(event.key.code) {
            case sf::Keyboard::W:
              player->goForward(true);
              break;
            case sf::Keyboard::S:
              player->goBack(true);
              break;
            case sf::Keyboard::A:
              player->goLeft(true);
              break;
            case sf::Keyboard::D:
              player->goRight(true);
              break;
            case sf::Keyboard::Space:
              player->goUp(true);
              break;
            case sf::Keyboard::LShift:
              player->goDown(true);
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
              player->goForward(false);
              break;
            case sf::Keyboard::S:
              player->goBack(false);
              break;
            case sf::Keyboard::A:
              player->goLeft(false);
              break;
            case sf::Keyboard::D:
              player->goRight(false);
              break;
            case sf::Keyboard::Space:
              player->goUp(false);
              break;
            case sf::Keyboard::LShift:
              player->goDown(false);
              break;
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

    axisList.call();

    glPopMatrix();

    //TODO: cursor
    //glBegin(GL_QUADS);

    //glVertex2f();

    //glEnd();

    window.display();
  }
  assets.reset();
  player.reset();
  world.reset();
}