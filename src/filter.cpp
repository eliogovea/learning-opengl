#include "iostream"

#include "filter.hpp"

#include "util.hpp"

filter::filter(mpu mpu_) : mpu_(mpu_) {}

// filter_0 no filter at all
filter_0::filter_0(mpu mpu_) : filter(mpu_) {}

bool filter_0::update() {
	if (!mpu_.read()) {
		return false;
	}

	// using accelerometer only
	glm::vec3 world_up{0, 0, 1};
	glm::vec3 g = {mpu_.acc.x, mpu_.acc.y, mpu_.acc.z};

	glm::mat4 model = glm::mat4{1};
	model_ = rotate(model, g, world_up);

	y_ = model_ * glm::vec4(0, 1, 0, 1);
	z_ = model_ * glm::vec4(1, 0, 0, 1);

	y_ = glm::normalize(y_);
	z_ = glm::normalize(z_);

	// TODO user gyro
	model_ = glm::rotate(model_, (float)(mpu_.gyro.x / 131.0 * M_PI / 180.0 * mpu_.dt), x());
	model_ = glm::rotate(model_, (float)(mpu_.gyro.y / 131.0 * M_PI / 180.0 * mpu_.dt), y());
	model_ = glm::rotate(model_, (float)(mpu_.gyro.z / 131.0 * M_PI / 180.0 * mpu_.dt), z());
	
	return true;
}
