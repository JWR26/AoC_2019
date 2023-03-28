#include "day_03.h"


void day_03::print_answers() {
	std::cout << "\n--- Day 3: Crossed Wires ---\n" << std::endl;

	std::vector<std::string> paths = helper::read_file("input\\day_03.txt");
	// test_03c answer is 651
	std::map<Point, int> wire_a = draw_wire(paths[0]);
	std::map<Point, int> wire_b = draw_wire(paths[1]);

	std::cout << "Part 1: " << find_closest_intersection(wire_a, wire_b) << std::endl;

	std::cout << "Part 2: " << find_quickest_intersection(wire_a, wire_b) << std::endl;
}


std::map<Point, int> day_03::draw_wire(const std::string& path) {
	Point origin(0, 0);
	int steps{ 0 };
	std::map<Point, int> wire_path;
	// get the instructions
	std::vector<std::string> instructions = helper::split_string(path, ',');
	// for each instruction
	for (size_t i = 0; i < instructions.size(); ++i) {
		// get the direction and number of moves
		char dir = instructions[i][0];
		int n = std::stoi(instructions[i].substr(1));
		for (int j = 0; j < n; ++j) {
			++steps;
			switch (dir) {
			case 'R':
				++origin.first;
				break;
			case 'L':
				--origin.first;
				break;
			case 'U':
				++origin.second;
				break;
			case 'D':
				--origin.second;
				break;
			default:
				std::cout << "Unexpected instruction encountered at " << i << ": " << dir << std::endl;
				break;
			}
			wire_path[origin] = steps;
		}
	}

	return wire_path;
}


int day_03::find_closest_intersection(const std::map<Point, int>& a, const std::map<Point, int>& b) {
	int closest{0};

	for (const auto& p : a) {
		if (b.find(p.first) != b.end()) {
			int distance = abs(p.first.first) + abs(p.first.second);
			if (distance < closest || closest == 0) {
				closest = distance;
			}
		}
	}

	return closest;
}


int day_03::find_quickest_intersection(const std::map<Point, int>& a, const std::map<Point, int>& b) {
	int quickest{ 0 };

	for (const auto& p : a) {
		if (b.find(p.first) != b.end()) {
			int distance = p.second + b.find(p.first)->second;
			if (distance < quickest || quickest == 0) {
				quickest = distance;
			}
		}
	}

	return quickest;
}

