#include "Game/object.h"

namespace Game {
Object::Object()
    : m_Position(0.0f, 0.0f), m_Size(1.0f, 1.0f), m_Velocity(0.0f), m_Color(1.0f), m_Rotation(0.0f), m_Sprite(), m_IsSolid(false), m_Destroyed(false) {}

Object::Object(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : m_Position(position), m_Size(size), m_Velocity(velocity), m_Color(color), m_Rotation(0.0f), m_Sprite(sprite), m_IsSolid(false), m_Destroyed(false) {}

void Object::Draw(SpriteRenderer& renderer) { renderer.DrawSprite(m_Sprite, m_Position, m_Size, m_Rotation, m_Color); }
} // namespace Game
