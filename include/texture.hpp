#pragma once

#include <string>

#include <GL/glew.h>

class texture {
public:
  explicit texture(const std::string& file_path);
  ~texture();
  void bind();
private:
  GLuint texture_id;
};
