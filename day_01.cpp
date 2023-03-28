#include "day_01.h"

void day_01::print_answers() {
	std::cout << "\n--- Day 1: The Tyranny of the Rocket Equation ---\n" << std::endl;

	std::vector<int> input = get_module_masses("input\\day_01.txt");

	std::cout << "Part 1: ";
	int total_fuel{ 0 };
	std::vector<int>::iterator it;
	for (it = input.begin(); it != input.end(); ++it) {
		total_fuel += fuel_for_module(*it);
	}
	std::cout << total_fuel << std::endl;

	total_fuel = 0;

	std::cout << "Part 2: ";
	for (it = input.begin(); it != input.end(); ++it) {
		total_fuel += fuel_for_module_and_fuel(*it);
	}
	std::cout << total_fuel << std::endl;
}

std::vector<int> day_01::get_module_masses(std::string path) {
	std::ifstream data{ path };
	std::vector<int> modules;
	modules.reserve(100); // 100 lines in the input file...

	while (data) {
		std::string line{};
		std::getline(data, line, '\n');

		if (!line.empty()) {
			int mass = std::stoi(line);
			modules.emplace_back(mass);
		}
	}

	return modules;
}

int day_01::fuel_for_module(int mass) {
	int fuel = mass / 3 - 2;
	if (fuel < 1) {
		return 0;
	}
	return fuel;
}

int day_01::fuel_for_module_and_fuel(int mass) {
	int fuel = mass / 3 - 2;
	if (fuel < 1) {
		return 0;
	}
	return fuel + fuel_for_module_and_fuel(fuel);
}