#include "day_02.h"

void day_02::print_answers() {
	std::cout << "\n--- Day 2: 1202 Program Alarm ---\n" << std::endl;

	std::vector<int> input = get_programme("input\\day_02.txt");

	// update position 1 with 12 and 2 with 2
	int noun{ 12 };
	int verb{ 2 };

	std::vector<int> output = update_programme(input, noun, verb);

	std::cout << "Part 1: " << output [0] << std::endl;

	for (int i = 1; i < 100; ++i) {
		for (int j = 1; j < 100; ++j) {
			std::vector<int> result = update_programme(input, i, j);
			if (result[0] == 19690720) {
				noun = i;
				verb = j;
			}
		}
	}

	std::cout << "Part 2: " << product(noun, verb) << std::endl;
}

std::vector<int> day_02::get_programme(const std::string& path) {
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

std::vector<int> day_02::update_programme(std::vector<int>& original, const int& n, const int& v) {
	
	std::vector<int> p(original);
	p[1] = n;
	p[2] = v;

	for (size_t i = 0; i < p.size(); i += 4) {
		if (p[i] == 99) {
			break;
		}

		size_t input_a = p[i + 1];
		size_t input_b = p[i + 2];
		size_t output = p[i + 3];
		
		if (p[i] == 1) {
			p[output] = p[input_a] + p[input_b];
		}
		else if (p[i] == 2) {
			p[output] = p[input_a] * p[input_b];
		}
	}

	return p;
}

int day_02::product(const int& noun, const int& verb) {
	return 100 * noun + verb;
}