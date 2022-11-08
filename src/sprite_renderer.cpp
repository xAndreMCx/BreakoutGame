#include "sprite_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGL/debug.h"
SpriteRenderer::SpriteRenderer(const Shader& shader) {
  m_Shader = shader;
  InitRenderData();
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::InitRenderData() {
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, 0.0f, 1.0f, //
      1.0f, 0.0f, 1.0f, 0.0f, //
      0.0f, 0.0f, 0.0f, 0.0f, //
                              //
      0.0f, 1.0f, 0.0f, 1.0f, //
      1.0f, 1.0f, 1.0f, 1.0f, //
      1.0f, 0.0f, 1.0f, 0.0f  //
  };

  GLCallV(glGenVertexArrays(1, &m_QuadVAO));
  GLCallV(glGenBuffers(1, &VBO));

  GLCallV(glBindBuffer(GL_ARRAY_BUFFER, VBO));
  GLCallV(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

  GLCallV(glBindVertexArray(m_QuadVAO));
  GLCallV(glEnableVertexAttribArray(0));
  GLCallV(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0));
  GLCallV(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GLCallV(glBindVertexArray(0));
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
  // prepare transformations
  m_Shader.Bind();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  m_Shader.SetUniform4m("model", model);
  m_Shader.SetUniform3f("spriteColor", color);

  // glActiveTexture(GL_TEXTURE0);
  texture.Bind(0);

  GLCallV(glBindVertexArray(m_QuadVAO));
  GLCallV(glDrawArrays(GL_TRIANGLES, 0, 6));

  GLCallV(glBindVertexArray(0));
}