#include <iostream>

#include "serial_reader.hpp"

reader::reader(std::string port, unsigned int rate) : io_(), serial_(io_, port) {
	serial_.set_option(boost::asio::serial_port_base::baud_rate(rate));
}

std::string reader::read_one() {
	char c;
	std::string result;
	bool started = false;
	while (true) {
		try {
		boost::asio::read(serial_, boost::asio::buffer(&c, 1));
		if (!started) {
			if (c == '<') {
				started = true;
			}
		} else {
			if (c == '>') {
				break;
			}
			if (c == ',') {
				c = ' ';
			}
			result += c;
		}
		} catch (...) {
			std::cout << "read error\n";
		}
	}
	return result;
}
