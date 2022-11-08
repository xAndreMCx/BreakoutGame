#pragma once
#include <vector>

#include "Game/level.h"

namespace Game {
enum class State { ACTIVE, MENU, WIN };

class Game {
private:
  State m_State;
  bool m_Keys[1024];
  unsigned int m_Width;
  unsigned int m_Height;
  unsigned int m_Level;
  std::vector<Level> m_Levels;

public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();
  void ProcessInput(float deltaTime);
  void Update(float deltaTime);
  void Render();

  unsigned int GetWidth() const;
  unsigned int GetHeight() const;
};

} // namespace Game
