#include "camera.hpp"

camera::camera(glm::vec3 position, glm::vec3 looking_at, glm::vec3 up) : position_(position), looking_at_(looking_at), up_(up) {}

glm::mat4& camera::get_matrix() {
  matrix_ = glm::lookAt(position_, looking_at_, up_);
  return matrix_;
}

void camera::move(glm::vec3 position) {
  position_ = position;
}

void camera::move(glm::vec3 direction, GLfloat distance) {
  position_ = position_ + glm::normalize(direction) * distance;
}

void camera::move_forward(GLfloat distance) {
  move(glm::normalize(position_ - looking_at_), distance);
}
