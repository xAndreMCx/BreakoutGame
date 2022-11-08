#include "OpenGL/shader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <sstream>

#include "OpenGL/debug.h"

Shader::Shader() : m_ID(0) {}

Shader::Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode) : m_ID(0) {
  m_ID = CreateShader(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
}

unsigned int Shader::CreateShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode) {
  unsigned int program = GLCall(glCreateProgram());
  unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
  unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
  unsigned int geometryShader = 0;

  if (!geometryShaderCode.empty()) {
    unsigned int geometryShader = CompileShader(GL_GEOMETRY_SHADER, geometryShaderCode);
    GLCallV(glAttachShader(program, geometryShader));
  }

  GLCallV(glAttachShader(program, vertexShader));
  GLCallV(glAttachShader(program, fragmentShader));
  GLCallV(glLinkProgram(program));
  GLCallV(glValidateProgram(program));

  int result;
  GLCallV(glGetProgramiv(program, GL_VALIDATE_STATUS, &result));
  if (!result) {
    int length;
    GLCallV(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
    std::unique_ptr<char[]> infoLog = std::make_unique<char[]>(length);
    GLCallV(glGetProgramInfoLog(program, length, NULL, infoLog.get()));
    std::cout << "Program failed validation:\n" << infoLog.get() << std::endl;
  }

  GLCallV(glDeleteShader(vertexShader));
  GLCallV(glDeleteShader(fragmentShader));
  GLCallV(glDeleteShader(geometryShader)); // will be ignored if it's 0

  return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
  unsigned int id = GLCall(glCreateShader(type));
  const char* src = source.c_str();
  GLCallV(glShaderSource(id, 1, &src, nullptr));
  GLCallV(glCompileShader(id));

  int result;
  GLCallV(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (!result) {
    int length;
    GLCallV(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    std::unique_ptr<char[]> infoLog = std::make_unique<char[]>(length);
    GLCallV(glGetShaderInfoLog(id, length, NULL, infoLog.get()));
    // TODO: add error message for geometry shader
    std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader failed to compile:\n" << infoLog.get() << std::endl;
    GLCallV(glDeleteShader(id));
    return 0;
  }
  return id;
}

Shader::~Shader() {} // GLCallV(glDeleteProgram(m_ID));

void Shader::Bind() const { GLCallV(glUseProgram(m_ID)); }

void Shader::Unbind() const { GLCallV(glUseProgram(0)); }

unsigned int Shader::GetID() const { return m_ID; }

int Shader::GetUniformLocation(const std::string& name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }
  int location = GLCall(glGetUniformLocation(m_ID, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: Uniform " << name << " does not exist" << std::endl;
  }
  m_UniformLocationCache[name] = location;
  return location;
}

void Shader::SetUniform1i(const std::string& name, int value) { GLCallV(glUniform1i(GetUniformLocation(name), value)); }

void Shader::SetUniform1f(const std::string& name, float value) { GLCallV(glUniform1f(GetUniformLocation(name), value)); }

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) { GLCallV(glUniform3f(GetUniformLocation(name), v0, v1, v2)); }

void Shader::SetUniform3f(const std::string& name, glm::vec3 value) { GLCallV(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z)); }

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) { GLCallV(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3)); }

void Shader::SetUniform4m(const std::string& name, const glm::mat4& value) {
  GLCallV(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
}