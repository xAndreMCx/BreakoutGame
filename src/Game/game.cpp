#include "game.h"

namespace Game {
Game::Game(unsigned int width, unsigned int height) : m_State(State::ACTIVE), m_Keys(), m_Width(width), m_Height(height) {}
Game::~Game() {}

void Game::Init() {}
void Game::ProcessInput(float deltaTime) {}
void Game::Update(float deltaTime) {}
void Game::Render() {}

} // namespace Game
