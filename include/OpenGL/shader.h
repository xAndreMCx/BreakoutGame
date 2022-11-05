#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader {
private:
  unsigned int m_ID;
  std::string m_VertexPath;
  std::string m_FragmentPath;
  std::unordered_map<std::string, int> m_UniformLocationCache;

  int GetUniformLocation(const std::string& name);
  unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
  unsigned int CompileShader(unsigned int type, const std::string& source);

public:
  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  ~Shader();

  void Bind();
  void Unbind();

  void SetUniform1f(const std::string& name, float value);
  void SetUniform3f(const std::string& name, float v0, float v1, float v2);
  void SetUniform3f(const std::string& name, glm::vec3 value);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void SetUniform1i(const std::string& name, int value);

  void SetUniformMat4f(const std::string& name, const glm::mat4 value);
};
