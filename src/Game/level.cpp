#include "Game/level.h"

#include <fstream>
#include <sstream>

#include "resource_manager.h"

namespace Game {
Level::Level() {}

void Level::Load(const std::string& filePath, unsigned int width, unsigned int height) {
  m_Bricks.clear();
  unsigned int tileCode;
  Level level;
  std::string line;
  std::ifstream levelFile(filePath.c_str());
  std::vector<std::vector<unsigned int>> tileData;

  if (levelFile) {
    while (std::getline(levelFile, line)) {
      std::istringstream lineSS(line);
      std::vector<unsigned int> row;
      while (lineSS >> tileCode) {
        row.push_back(tileCode);
      }
      tileData.push_back(row);
    }
    if (tileData.size() > 0) {
      Init(tileData, width, height);
    }
  }
}

void Level::Draw(SpriteRenderer& renderer) {
  for (Object& tile : m_Bricks)
    if (!tile.m_Destroyed) {
      tile.Draw(renderer);
    }
}

bool Level::IsCompleted() {
  for (Object& tile : m_Bricks)
    if (!tile.m_IsSolid && !tile.m_Destroyed) {
      return false;
    }
  return true;
}

void Level::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int width, unsigned int height) {
  unsigned int _height = tileData.size();
  unsigned int _width = tileData[0].size();
  float unitHeight = _height / height;
  float unitWidth = _width / static_cast<float>(width);

  for (unsigned int y = 0; y < _height; ++y) {
    for (unsigned int x = 0; x < _width; ++x) {
      // check block type from level data (2D level array)
      if (tileData[y][x] == 1) // solid
      {
        glm::vec2 pos(unitWidth * x, unitHeight * y);
        glm::vec2 size(unitWidth, unitHeight);
        Object obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
        obj.m_IsSolid = true;
        m_Bricks.push_back(obj);
      } else if (tileData[y][x] > 1) {
        glm::vec3 color = glm::vec3(1.0f); // original: white
        if (tileData[y][x] == 2)
          color = glm::vec3(0.2f, 0.6f, 1.0f);
        else if (tileData[y][x] == 3)
          color = glm::vec3(0.0f, 0.7f, 0.0f);
        else if (tileData[y][x] == 4)
          color = glm::vec3(0.8f, 0.8f, 0.4f);
        else if (tileData[y][x] == 5)
          color = glm::vec3(1.0f, 0.5f, 0.0f);

        glm::vec2 pos(unitWidth * x, unitHeight * y);
        glm::vec2 size(unitWidth, unitHeight);
        m_Bricks.push_back(Object(pos, size, ResourceManager::GetTexture("block"), color));
      }
    }
  }
}

} // namespace Game
