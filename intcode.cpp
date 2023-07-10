#include "intcode.h"

std::vector<int> intcode::get_programme(const std::string& path) {
	std::ifstream data{ path };
	std::vector<int> ints;
	ints.reserve(500); // arbitrary number bigger than the list

	while (data) {
		std::string line{};
		std::getline(data, line, ',');

		if (!line.empty()) {
			int mass = std::stoi(line);
			ints.emplace_back(mass);
		}
	}

	return ints;
}


std::vector<long long int> intcode::get_long_programme(const std::string& path) {
	std::ifstream data{ path };
	std::vector<long long int> ints;
	ints.reserve(500); // arbitrary number bigger than the list

	while (data) {
		std::string line{};
		std::getline(data, line, ',');

		if (!line.empty()) {
			long long int mass = std::stoll(line);
			ints.emplace_back(mass);
		}
	}

	return ints;
}

