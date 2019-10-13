#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

class shader {
public:
  static std::string load(const std::string filepath);
  static GLuint compile(GLuint type, const std::string& code);
  static GLuint link(const std::vector<GLuint>& shaders);
};

#endif
