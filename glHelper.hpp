#pragma once

#include <vector>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glext.h>
#include <gl/wglext.h>

#include "types.hpp"

//GL_ARB_vertex_buffer_object extension pointers
PFNGLBINDBUFFERARBPROC           glBindBufferARB = nullptr;
PFNGLDELETEBUFFERSARBPROC        glDeleteBuffersARB = nullptr;
PFNGLGENBUFFERSARBPROC           glGenBuffersARB = nullptr;
PFNGLISBUFFERARBPROC             glIsBufferARB = nullptr;
PFNGLBUFFERDATAARBPROC           glBufferDataARB = nullptr;
PFNGLBUFFERSUBDATAARBPROC        glBufferSubDataARB = nullptr;
PFNGLGETBUFFERSUBDATAARBPROC     glGetBufferSubDataARB = nullptr;
PFNGLMAPBUFFERARBPROC            glMapBufferARB = nullptr;
PFNGLUNMAPBUFFERARBPROC          glUnmapBufferARB = nullptr;
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB = nullptr;
PFNGLGETBUFFERPOINTERVARBPROC    glGetBufferPointervARB = nullptr;

class GlHelper {
  GLdouble aspect_ = 0;
public:
  bool vboSupport = false;
  //bool vaoSupport;

  std::wstring vendor;
  std::wstring renderer;
  std::wstring version;
  std::vector<std::wstring> extensions;

  void init2D(GLdouble width, GLdouble height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    gluOrtho2D(0, 0, width, height);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
  }

  void init3D(GLdouble width, GLdouble height) {
    if(height != 0) {
      aspect_ = width / height;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    gluPerspective(60, aspect_, 0.05, 200);

    glFrontFace(GL_CCW);
    glLineWidth(3);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
  }

  bool isExtensionSupport(std::wstring name) {
    bool found = false;
    for(std::size_t i = 0; i < extensions.size(); i++) {
      found = extensions[i] == name || found;
    }
    return found;
  }

  void loadInfo() {
    vendor = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
    vendor.shrink_to_fit();

    renderer = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
    renderer.shrink_to_fit();

    version = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    version.shrink_to_fit();

    std::wstring extensionslist = wide(std::string(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS))));
    std::size_t lastPos = 0;
    extensions.reserve(300);
    for(std::size_t i = 0; i < extensionslist.length(); i++) {
      if(extensionslist[i] == L' ') {
        extensions.push_back(extensionslist.substr(lastPos == 0 ? 0 : lastPos + 1, i - lastPos));
        extensions.back().shrink_to_fit();
        lastPos = i;
      }
    }
    extensions.shrink_to_fit();

#ifdef DEBUG
    std::wcout << L"OpenGL info: " << std::endl;
    std::wcout << L"GL_VENDOR:\t" << vendor << std::endl;
    std::wcout << L"GL_RENDERER:\t" << renderer << std::endl;
    std::wcout << L"GL_VERSION:\t" << version << std::endl;
    std::wcout << L"GL_EXTENSIONS:" << std::endl;
    for(std::size_t i = 0; i < extensions.size(); i++) {
      std::wcout << extensions[i] << std::endl;
    }
    std::wcout << L"Loading OpenGL extensions" << std::endl;
#endif // DEBUG
  }

  void loadExtensions() {
    //Taking functions pointers
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
    glIsBufferARB = (PFNGLISBUFFERARBPROC) wglGetProcAddress("glIsBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
    glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) wglGetProcAddress("glBufferSubDataARB");
    glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC) wglGetProcAddress("glGetBufferSubDataARB");
    glMapBufferARB = (PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB");
    glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");
    glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) wglGetProcAddress("glGetBufferParameterivARB");
    glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC) wglGetProcAddress("glGetBufferPointervARB");

    //Veryfying pointers for null
    if(glBindBufferARB &&
       glDeleteBuffersARB &&
       glGenBuffersARB &&
       glIsBufferARB &&
       glBufferDataARB &&
       glBufferSubDataARB &&
       glGetBufferSubDataARB &&
       glMapBufferARB &&
       glUnmapBufferARB &&
       glGetBufferParameterivARB &&
       glGetBufferPointervARB) {
#ifdef DEBUG
      std::wcout << L"VBO extension loaded" << std::endl;
#endif // DEBUG
      vboSupport = true;
    }
#ifdef DEBUG
    else {
      std::wcout << L"VBO extension NOT loaded" << std::endl;
    }
#endif // DEBUG
  }
};