#pragma once

#include "glad.h"

class DisplayList {
public:

  DisplayList();

  explicit DisplayList(const GLenum mode);

  ~DisplayList();

  void begin() ;

  void begin(const GLenum mode) ;

  void end() ;

  void call() const;
protected:

  GLuint handle_ = 0;
};
