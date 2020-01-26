#include "camera.hpp"

camera::camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) : position_(position), 
   forward_(glm::normalize(forward)), 
   up_(up),
   right_(glm::normalize(glm::cross(forward, up)))
{}

glm::mat4& camera::get_matrix() {
  matrix_ = glm::lookAt(position_, position_ + forward_, up_);
  return matrix_;
}

void camera::move(glm::vec3 position) {
  position_ = position;
}

void camera::move(glm::vec3 direction, GLfloat distance) {
  position_ = position_ + glm::normalize(direction) * distance;
}

void camera::move_forward(GLfloat distance) {
  move(forward_, distance);
}

void camera::move_right(GLfloat distance) {
  move(right_, distance);
}

void camera::move_up(GLfloat distance) {
  move(up_, distance);
}

void camera::look_at(glm::vec3 target) {
  forward_ = glm::normalize(target - position_);
  // TODO
}
