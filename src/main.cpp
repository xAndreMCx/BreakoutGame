#include <GLAD/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Game/game.h"
#include "OpenGL/debug.h"
#include "resource_manager.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}
Game::Game Breakout(WIDTH, HEIGHT);
int main(void) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Breakout", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cerr << "Failed to initialize OpenGL contex" << std::endl;
  }
  // TODO: move OpenGL calls out to a other file
  GLCallV(glViewport(0, 0, WIDTH, HEIGHT));
  GLCallV(glEnable(GL_BLEND));

  GLCallV(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  Breakout.Init();

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;


  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    Breakout.ProcessInput(deltaTime);

    Breakout.Update(deltaTime);

    GLCallV(glClearColor(0.3f, 0.1f, 0.7f, 1.0f));
    GLCallV(glClear(GL_COLOR_BUFFER_BIT));

    Breakout.Render();

    glfwSwapBuffers(window);
  }

  // TODO: should maybe distroy resource manager here
  ResourceManager::Clear();
  glfwTerminate();

  return 0;
}