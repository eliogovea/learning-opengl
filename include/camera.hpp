#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera {
public:
  explicit camera(glm::vec3 position, glm::vec3 looking_at, glm::vec3 up);
  glm::mat4& get_matrix();
  void move(glm::vec3 position);
  void move(glm::vec3 direction, GLfloat distance);
  void move_forward(GLfloat distance);
private:
  glm::vec3 position_{0.0, 0.0, 0.0};
  glm::vec3 looking_at_{0.0, 0.0, 0.0};
  glm::vec3 up_{0.0, 1.0, 0.0};
  glm::mat4 matrix_;
};
