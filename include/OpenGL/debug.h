#pragma once

#include <GLAD/gl.h>

#include <cassert>
#include <iostream>

#ifdef _DEBUG
  #define GLCallV(x) \
    GLClearErrors(); \
    x;               \
    assert(GLLogCall(#x, __FILE__, __LINE__))

  #define GLCall(x)                              \
    [&]() {                                      \
      GLClearErrors();                           \
      auto retVal = x;                           \
      assert(GLLogCall(#x, __FILE__, __LINE__)); \
      return retVal;                             \
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
    std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}
