#include "Game/game.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Game/level.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer* renderer;

namespace Game {
Game::Game(unsigned int width, unsigned int height) : m_State(State::ACTIVE), m_Keys(), m_Width(width), m_Height(height) {}
Game::~Game() { delete renderer; }

void Game::Init() {
  ResourceManager::LoadShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl", "", "sprite");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()), 0.0f, -1.0f, 1.0f);
  Shader shader = ResourceManager::GetShader("sprite");
  shader.Bind();
  shader.SetUniform1i("image", 0);
  shader.SetUniform4m("projection", projection);

  renderer = new SpriteRenderer(shader);
  ResourceManager::LoadTexture("assets/textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("assets/textures/awesomeface.png", true, "face");
  ResourceManager::LoadTexture("assets/textures/block.png", false, "block");
  ResourceManager::LoadTexture("assets/textures/block_solid.png", false, "block_solid");

  Level levelOne, levelTwo, levelThree, levelFour;
  levelOne.Load("assets/levels/01.txt", m_Width, m_Height / 2);
  levelTwo.Load("assets/levels/02.txt", m_Width, m_Height / 2);
  levelThree.Load("assets/levels/03.txt", m_Width, m_Height / 2);
  levelFour.Load("assets/levels/04.txt", m_Width, m_Height / 2);

  m_Levels.push_back(levelOne);
  m_Levels.push_back(levelTwo);
  m_Levels.push_back(levelThree);
  m_Levels.push_back(levelFour);

  m_Level = 0;
}
void Game::ProcessInput(float deltaTime) {}
void Game::Update(float deltaTime) {}
void Game::Render() {
  if (m_State == State::ACTIVE) {
    renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f), glm::vec2(m_Width, m_Height));
    m_Levels[m_Level].Draw(*renderer);
  }

  renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 300.0f), 45.0f, glm::vec3(0.1f, 0.6f, 0.6f));
}

unsigned int Game::GetWidth() const { return m_Width; }
unsigned int Game::GetHeight() const { return m_Height; }
} // namespace Game
