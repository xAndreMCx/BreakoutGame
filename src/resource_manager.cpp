#include "resource_manager.h"

#include <stb_image.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "OpenGL/shader.h"
#include "OpenGL/texture.h"

// Instantiate static variables
std::unordered_map<std::string, Texture2D> ResourceManager::Textures;
std::unordered_map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath,
    const std::string& shaderName) {
  Shaders[shaderName] = LoadShaderFromFile(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
  return Shaders[shaderName];
}

Texture2D ResourceManager::LoadTexture(const std::string& texturePath, bool alpha, const std::string& textureName) {
  Textures[textureName] = LoadTextureFromFile(texturePath, alpha);
  return Textures[textureName];
}

Shader ResourceManager::GetShader(const std::string& shaderName) { return Shaders[shaderName]; }

Texture2D ResourceManager::GetTexture(const std::string& textureName) { return Textures[textureName]; }

// // TODO: Make sure shaders and textures gets destroyed
// void ResourceManager::Clear() {
//   // (properly) delete all shaders
//   for (auto _shader : Shaders) {
//     _shader
//   }
//   // (properly) delete all textures
//   for (auto iter : Textures) GLCallV(glDeleteTextures(1, &iter.second.ID));
// }

std::string ResourceManager::LoadShaderCode(const std::string& filePath) {
  std::string shaderCode{""};
  try {
    // open file
    std::ifstream shaderFile(filePath);

    // read file's buffer contents into streams
    std::stringstream shaderSS;
    shaderSS << shaderFile.rdbuf();

    // close file
    shaderFile.close();

    shaderCode = shaderSS.str();

  } catch (const std::exception& e) {
    std::cerr << "ERROR::SHADER: Failed to read shader files. " << e.what() << std::endl;
  }
  return shaderCode;
}

Shader ResourceManager::LoadShaderFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;

  // retrieve the vertex/fragment source code from filePath
  vertexCode = LoadShaderCode(vertexShaderPath);
  fragmentCode = LoadShaderCode(fragmentShaderPath);
  geometryCode = (!geometryShaderPath.empty()) ? geometryCode = LoadShaderCode(geometryShaderPath) : "";

  Shader shader(vertexCode, fragmentCode, geometryCode);
  return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const std::string& texturePath, bool alpha) {
  int width;
  int height;
  int nrChannels;

  // load image
  stbi_set_flip_vertically_on_load(1);
  unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

  Texture::Format textureFormat = (alpha) ? Texture::Format::RGBA : Texture::Format::RGB;
  Texture::Format imageFormat = (alpha) ? Texture::Format::RGBA : Texture::Format::RGB;

  Texture2D texture(width, height, data, textureFormat, imageFormat);

  stbi_image_free(data);

  return texture;
}