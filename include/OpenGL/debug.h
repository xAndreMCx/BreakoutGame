#pragma once

#include <GLAD/gl.h>

#include <iostream>
#define _DEBUG
#ifdef _DEBUG
  #define GLCallV(x) \
    GLClearErrors(); \
    x;               \
    if (GLLogCall(#x, __FILE__, __LINE__)) __builtin_trap();


  #define GLCall(x)                                            \
    [&]() {                                                    \
      GLClearErrors();                                         \
      auto retVal = x;                                         \
      if (GLLogCall(#x, __FILE__, __LINE__)) __builtin_trap(); \
      return retVal;                                           \
    }()

#else
  #define GLCallV(x) x;
  #define GLCall(x) [&]() { return x; }()
#endif

static void GLClearErrors() {
  while (glGetError() != GL_NO_ERROR) {
  }
}

static bool GLLogCall(const char* function, const char* file, int line) {
  while (GLenum error = glGetError()) {
    std::cerr << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
    return true;
  }
  return false;
}
