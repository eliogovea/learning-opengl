#pragma once

#include <string>
#include <boost/asio.hpp>

class reader {
public:
	reader(std::string port, unsigned int rate);
	std::string read_one();
	// TODO std::vector<int> parse();
private:
	boost::asio::io_service io_;
	boost::asio::serial_port serial_;
};
