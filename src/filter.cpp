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
	// model_ = glm::rotate(model_, (float)(mpu_.gyro.x / 131.0 * M_PI / 180.0 * mpu_.dt), x());
	// model_ = glm::rotate(model_, (float)(mpu_.gyro.y / 131.0 * M_PI / 180.0 * mpu_.dt), y());
	// model_ = glm::rotate(model_, (float)(mpu_.gyro.z / 131.0 * M_PI / 180.0 * mpu_.dt), z());
	
	return true;
}

/// complementary filter

filter_complementary::filter_complementary(mpu mpu_) : filter(mpu_) {}

bool filter_complementary::update() {
	if (!mpu_.read()) {
		return false;
	}
	
	// TODO gyro to radians ???

	float wa = glm::length(mpu_.gyro) * mpu_.dt;

	glm::quat delta_qw{wa, glm::normalize(mpu_.gyro)};
	delta_qw = glm::normalize(delta_qw);

	std::cout << "w:  " << mpu_.gyro.x << " " << mpu_.gyro.y << " " << mpu_.gyro.z << " " << wa << "\n";

	qw_ = qw_ * delta_qw;

	// model_ = glm::mat4_cast(qw_); return true;

	float ax = (float)mpu_.acc.x;
	float ay = (float)mpu_.acc.y;
	float az = (float)mpu_.acc.z;

	sum_ax_ += mpu_.acc.x;
	sum_ay_ += mpu_.acc.y;
	sum_az_ += mpu_.acc.z;

	steps_++;

	if (steps_ < max_steps_) {
		return false;
	}

	sum_ax_ /= (float)steps_;
	sum_ay_ /= (float)steps_;
	sum_az_ /= (float)steps_;
	steps_ = 0;

	glm::vec3 a{sum_ax_, sum_ay_, sum_az_};
	glm::vec3 world_up{0, 0, 1};
	
	glm::vec3 n = glm::cross(a, world_up);
	std::cout << "|n| = " << glm::length(n) << "\n";

	// TODO if n ~ (0, 0, 0)

	n = glm::normalize(n);

	glm::quat qa{get_angle(glm::normalize(a), world_up), n};

	model_ = glm::mat4_cast(qa); return true;

	glm::quat qc = glm::quat{get_angle(a, world_up), n};

	// model_ = glm::mat4_cast(qc);

	// std::cout << "qw: " << qw_.x << " " << qw_.y << " " << qw_.z << " " << qw_.w << "\n";

	return true;
}
