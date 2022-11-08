#pragma once
#include <string>
#include <vector>

#include "Game/object.h"

namespace Game {
class Level {
private:
  std::vector<Object> m_Bricks;


public:
  Level();
  bool IsCompleted();
  void Draw(SpriteRenderer& renderer);
  void Load(const std::string& filePath, unsigned int width, unsigned int height);
  void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int width, unsigned int height);
};

} // namespace Game
