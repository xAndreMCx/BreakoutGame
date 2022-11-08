#pragma once
#include <glm/glm.hpp>

#include "OpenGL/texture.h"
#include "sprite_renderer.h"

namespace Game {
class Object {
private:
public:
  glm::vec2 m_Position;
  glm::vec2 m_Size;
  glm::vec2 m_Velocity;
  glm::vec3 m_Color;
  float m_Rotation;
  bool m_Destroyed;
  Texture2D m_Sprite;
  bool m_IsSolid;
  Object();
  Object(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

  virtual void Draw(SpriteRenderer& renderer);
};

} // namespace Game
