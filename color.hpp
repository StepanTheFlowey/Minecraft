#pragma once
#include <Windows.h>
#include <gl\GL.h>

class Color {
public:
  GLubyte r;
  GLubyte g;
  GLubyte b;
  GLubyte a;

  //Default constructor
  Color();

  //Default destructor
  Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A = 255);

  //Calls glColor(r,g,b,a)
  inline void glColor() const;
};