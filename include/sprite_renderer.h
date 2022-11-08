#pragma once

#include "OpenGL/shader.h"
#include "OpenGL/texture.h"

class SpriteRenderer {
public:
  SpriteRenderer(const Shader& shader);
  ~SpriteRenderer();

  void DrawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
      glm::vec3 color = glm::vec3(1.0f));

private:
  Shader m_Shader;
  unsigned int m_QuadVAO;

  void InitRenderData();
};