#include "day_06.h"

void day_06::print_answers() {
	std::cout << "\n--- Day 6: Universal Orbit Map ---\n" << std::endl;

	std::vector<std::string> input = helper::read_file("input\\day_06.txt");
	std::map <std::string, std::vector<std::string>> m = get_map(input, ')');

	int part_1{ 0 };

	for (const auto& k: m) {
		part_1 += total_orbits(m, k.first, 0);
	}

	std::cout << "Part 1: " << part_1 << std::endl;

	std::cout << "Part 2: " << std::endl;

}

std::map <std::string, std::vector<std::string>> day_06::get_map(const std::vector<std::string> list, const char& c) {
	std::map <std::string, std::vector<std::string>> m{};
	
	std::string obj_a{};
	std::string obj_b{};

	for (const std::string& str : list) {
		std::vector<std::string> objects = helper::split_string(str, c);
		obj_a = objects[0];
		obj_b = objects[1];
		if (m.find(obj_a) != m.end()) {
			m[obj_a].push_back(obj_b);
		}
		else {
			std::vector<std::string> children = { obj_b };
			m[obj_a] = children;
		}
	}

	return m;
}

int day_06::total_orbits(const std::map <std::string, std::vector<std::string>>& m, const std::string& str, const int& i) {

	if (m.find(str) == m.end()) {
		return 0;
	}

	int total{ 0 };
	for (const auto& s : m.find(str)->second) {
		++total;
		total += total_orbits(m, s, i+1);
	}

	return total;
}
