#include "GlHelper.hpp"

#include "DisplayHelper.hpp"
#include <gl/GLU.h>

GlHelper* gl = nullptr;

void GlHelper::init2D() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glViewport(
    0,
    0,
    static_cast<GLsizei>(display->videoMode.width),
    static_cast<GLsizei>(display->videoMode.height)
  );

  gluOrtho2D(
    -(display->videoMode.width / 2.0),
    display->videoMode.width / 2.0,
    display->videoMode.height / 2.0,
    -(display->videoMode.height / 2.0)
  );

  glDisable(GL_DEPTH_TEST);
}

void GlHelper::init3D() {
  if(display->videoMode.height != 0) {
    aspect_ = static_cast<GLdouble>(display->videoMode.width) / display->videoMode.height;
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glViewport(
    0,
    0,
    static_cast<GLsizei>(display->videoMode.width),
    static_cast<GLsizei>(display->videoMode.height)
  );
  gluPerspective(70, aspect_, 1e-2, 1e+3);

  glEnable(GL_DEPTH_TEST);
}

bool GlHelper::isExtensionSupport(const std::wstring name) const {
  return extensions.find(name) != extensions.end();
}

void GlHelper::loadInfo() {
  vendor = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
  vendor.shrink_to_fit();

  renderer = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
  renderer.shrink_to_fit();

  version = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
  version.shrink_to_fit();

  std::wstring extensionslist = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS))));
  std::size_t lastPos = 0;
  for(std::size_t i = 0; i < extensionslist.length(); ++i) {
    if(extensionslist[i] == L' ') {
      extensions.insert(extensionslist.substr(lastPos == 0 ? 0 : lastPos + 1, i - lastPos));
      lastPos = i;
    }
  }

#ifdef DEBUG
  std::wcout << L"OpenGL info:" << std::endl;
  std::wcout << L"GL_VENDOR:\t" << vendor << std::endl;
  std::wcout << L"GL_RENDERER:\t" << renderer << std::endl;
  std::wcout << L"GL_VERSION:\t" << version << std::endl;
  std::wcout << L"GL_EXTENSIONS:" << std::endl;
  for(const auto& i : extensions)
    std::wcout << i << std::endl;

  GLint num;
  glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &num);
  std::wcout << L"GL_MAX_MODELVIEW_STACK_DEPTH:\t" << num << std::endl;
  glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &num);
  std::wcout << L"GL_MAX_PROJECTION_STACK_DEPTH:\t" << num << std::endl;
  glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &num);
  std::wcout << L"GL_MAX_TEXTURE_STACK_DEPTH:\t" << num << std::endl;
#endif // DEBUG
}

void GlHelper::loadGL() {
  gladLoadGL();
}

void GlHelper::initGL() {
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClearDepth(0.0);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GlHelper::clearInfo() {
  vendor.clear();
  renderer.clear();
  version.clear();
  version.clear();
  extensions.clear();
}

void GlHelper::checkForErrors(const char* file, const uint32_t line) {
  GLenum e = glGetError();
  if(e == GL_NO_ERROR) return;
  std::wcout << wide(file) << L':' << line << " error ";
  switch(e) {
    case GL_INVALID_ENUM:
      std::wcout << L"GL_INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      std::wcout << L"GL_INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      std::wcout << L"GL_INVALID_OPERATION";
      break;
    case GL_STACK_OVERFLOW:
      std::wcout << L"GL_STACK_OVERFLOW";
      break;
    case GL_STACK_UNDERFLOW:
      std::wcout << L"GL_STACK_UNDERFLOW";
      break;
    case GL_OUT_OF_MEMORY:
      std::wcout << L"GL_OUT_OF_MEMORY";
      break;
  }
  std::wcout << std::endl;
}
