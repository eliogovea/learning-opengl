#pragma once

#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera {
public:
  explicit camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
  glm::mat4& get_matrix();
  void move(glm::vec3 position);
  void move(glm::vec3 direction, GLfloat distance);
  void move_forward(GLfloat distance);
  void move_right(GLfloat distance);
  void move_up(GLfloat distance);
  void look_at(glm::vec3 target);
private:
  glm::vec3 position_;
  glm::vec3 forward_;
  glm::vec3 right_;
  glm::vec3 up_;
  glm::mat4 matrix_;
};
