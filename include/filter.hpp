#pragma once

#include <iostream>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "serial_reader.hpp"

struct mpu {
	glm::vec3 acc;
	glm::vec3 gyro;
	float dt;
	reader& serial;

	mpu(reader& serial) : serial(serial) {}

	bool read() {
		try {
			auto line = serial.read_one();
			std::stringstream ss(line);
			ss >> acc.x >> acc.y >> acc.z >> gyro.x >> gyro.y >> gyro.z >> dt;
			acc.x /= 16384.0;
			acc.y /= 16384.0;
			acc.z /= 16384.0;
			gyro.x /= 131.0;
			gyro.y /= 131.0;
			gyro.z /= 131.0;
			dt *= 0.001;
			return true;
		} catch (...) {
			std::cout << "read error\n";
		}
		return false;
/*
		// TODO read from accelerometer
		// mocking
		static int step = 0;
		float s = 10 * sin(0.01 * (float)step);
		float c = 10 * cos(0.01 * (float)step);
		step++;
		acc = {0, c, s};
		gyro = {0, 0, 0};
		return true;
*/
	}
};

class filter {
public:
	filter(mpu mpu_);
	virtual bool update() = 0;
	const glm::vec3 x() {
		return glm::normalize(glm::cross(y_, z_));
	}
	const glm::vec3 y() {
		return y_;
	}
	const glm::vec3 z() {
		return z_;
	}
	const mpu& get_mpu() {
		return mpu_;
	}
	const glm::mat4& model() {
		return model_;
	}
protected:
	mpu mpu_;
	glm::vec3 y_{0, 1, 0}; // forward
	glm::vec3 z_{0, 0, 1}; // up
	glm::mat4 model_{1};
};

class filter_0 : public filter {
public:
	filter_0(mpu mpu_);
	bool update() override;
};

class filter_complementary : public filter {
public:
	filter_complementary(mpu mpu_);
	bool update() override;
private:
	glm::quat qw_{1, 0, 0, 0};
	float sum_ax_{0}, sum_ay_{0}, sum_az_{0};
	int steps_{0};
	int max_steps_{5};
};
