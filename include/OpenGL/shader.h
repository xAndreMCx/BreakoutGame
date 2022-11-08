#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
private:
  unsigned int m_ID;
  std::unordered_map<std::string, int> m_UniformLocationCache;

  unsigned int CreateShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode);
  unsigned int CompileShader(unsigned int type, const std::string& source);
  int GetUniformLocation(const std::string& name);

public:
  // Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
  Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode);
  Shader();
  ~Shader();

  void Bind() const;
  void Unbind() const;

  unsigned int GetID() const;

  void SetUniform1f(const std::string& name, float value);
  void SetUniform3f(const std::string& name, float v0, float v1, float v2);
  void SetUniform3f(const std::string& name, glm::vec3 value);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void SetUniform1i(const std::string& name, int value);
  void SetUniform4m(const std::string& name, const glm::mat4& value);
};
