#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

float get_angle(const glm::vec3 P, const glm::vec3 Q);
glm::mat4 rotate(glm::mat4 model, const glm::vec3 axis, const glm::vec3 new_axis);


