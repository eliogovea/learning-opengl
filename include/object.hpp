#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

struct vertex {
  glm::vec3 position;
  // TODO add color, ...
};

class object {
public:
  explicit object(const std::string& file_path);
  explicit object(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices);
  ~object();

  void init();
  void render();
private:
  std::vector<vertex> vertices_;
  std::vector<GLuint> indices_;
  GLuint va_, vb_, eb_;
};
