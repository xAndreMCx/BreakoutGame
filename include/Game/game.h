#pragma once

namespace Game {
enum State {
  ACTIVE,
  MENU,
  WIN
};

class Game {
private:
  State m_State;
  bool m_Keys[1024];
  unsigned int m_Width;
  unsigned int m_Height;

public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();
  void ProcessInput(float deltaTime);
  void Update(float deltaTime);
  void Render();
};

} // namespace Game
