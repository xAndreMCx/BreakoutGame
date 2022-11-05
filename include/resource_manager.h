#pragma once

#include <string>
#include <unordered_map>

#include "OpenGL/shader.h"
#include "OpenGL/texture.h"

class ResourceManager {
private:
  ResourceManager();
  static std::string LoadShaderCode(const std::string& filePath);
  static Shader LoadShaderFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath = "");
  static Texture2D LoadTextureFromFile(const std::string& texturePath, bool alpha);

public:
  static std::unordered_map<std::string, Shader> Shaders;
  static std::unordered_map<std::string, Texture2D> Textures;

  static Shader LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath,
      const std::string& shaderName);
  static Texture2D LoadTexture(const std::string& texturePath, bool alpha, const std::string& textureName);

  static Shader GetShader(const std::string& shaderName);
  static Texture2D GetTexture(const std::string& textureName);
  static void Clear();
};
