#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <map>

class shader {
public:
  static std::string load(const std::string filepath);
  static GLuint compile(GLuint type, const std::string& code);
  static GLuint link(const std::vector<GLuint>& shaders);
  explicit shader(const std::string& vertex_shader, const std::string& fragment_shader);
  ~shader();
  GLuint program_id();
  GLuint locate_uniform(const std::string& name);
  bool bind();
private:
  GLuint program_id_;
  std::map<std::string, GLuint> uniforms_;
};

#endif
