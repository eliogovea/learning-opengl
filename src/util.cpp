#include <iostream>

#include "util.hpp"

float get_angle(const glm::vec3 P, const glm::vec3 Q) {
  	float c = glm::length(glm::cross(P, Q));
	float d = glm::dot(P, Q);
	return (float)atan2(c, d);	
};

glm::mat4 rotate(glm::mat4 model, const glm::vec3 axis, const glm::vec3 new_axis) {
  	auto n = glm::cross(axis, new_axis);
	const double eps = 1e-9;
	if (abs(n.x) < eps && abs(n.y) < eps && abs(n.z) < eps) {
		return glm::mat4{1};
	}
	n = glm::normalize(n);
	auto a = get_angle(axis, new_axis);
	std::cout << "normal " << n.x << "\t" << n.y << "\t" << n.z << "\n";
	std::cout << "angle " << a << "\n";
	std::cout << "\n";
	return glm::rotate(model, a, n);
};
