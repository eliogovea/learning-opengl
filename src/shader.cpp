#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <GL/glew.h>

#include "shader.hpp"

std::string shader::load(const std::string file_path) {
  std::string result;
  std::ifstream input{file_path.data(), std::ios::in};
  if (!input.is_open()) {
    // should throw an exception ???
    std::cout << "could not load the shader " << file_path << std::endl;
  }
  std::string line;
  while (getline(input, line)) {
    result += line + "\n";
  }
  return result;
}

// type: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
GLuint shader::compile(GLuint type, const std::string& code) {
  GLuint id = glCreateShader(type);
  
  GLchar const* ptr = (const GLchar*)code.c_str();
  glShaderSource(id, 1, &ptr, 0);
  glCompileShader(id);

  GLint result = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    GLint msg_length = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msg_length);
    if (msg_length > 0) {
      std::vector<char> msg(msg_length);
      glGetShaderInfoLog(id, msg_length, nullptr, &msg[0]);
      std::cout << "error compiling shader: " << msg.data() << std::endl;
      glDeleteShader(id);
    }
  }
  return id;
}

GLuint shader::link(const std::vector<GLuint>& shaders) {
  GLuint id = glCreateProgram();
  for (auto x : shaders) {
    glAttachShader(id, x);
  }
  glLinkProgram(id);

  GLint result = 0;

  glGetProgramiv(id, GL_LINK_STATUS, &result);
  
  if (result == GL_FALSE) {
    GLint msg_length = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &msg_length);
    if (msg_length > 0) {
      std::vector<char> msg(msg_length + 1);
      glGetProgramInfoLog(id, msg_length, nullptr, &msg[0]);
      std::cout << "error linking: " << msg.data() << std::endl;
    }
    glDeleteProgram(id);
    for (auto x : shaders) {
      glDeleteShader(x);
    }
    return id;
  }

  glValidateProgram(id);

  if (result == GL_FALSE) {
    GLint msg_length = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &msg_length);
    if (msg_length > 0) {
      std::vector<char> msg(msg_length + 1);
      glGetProgramInfoLog(id, msg_length, nullptr, &msg[0]);
      std::cout << "error validating: " << msg.data() << std::endl;
    }
    glDeleteProgram(id);
    for (auto x : shaders) {
      glDeleteShader(x);
    }
    return id;
  }

  for (auto x : shaders) {
    glDetachShader(id, x);
  }
  for (auto x : shaders) {
    glDeleteShader(x);
  }
  return id;
}
