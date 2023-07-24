#include "day_19.h"

const std::string INPUT_FILE {"input\\day_19.txt"};
const long long int MAX_POS{ 50 };


bool all_equal_to(const long long int& a, const long long int& b, const long long int& c, const long long int& n) {
	return (a == n && b == n && c == n);
}


long long int get_output(const long long int& x, const long long int& y) {
	std::vector<long long int> input { intcode::get_long_programme(INPUT_FILE) };
	Intcode drone(input);
	std::vector<long long int> drone_input({ x, y });
	drone.update_input(drone_input);
	return drone.run_programme().back();
}


void day_19::print_answers() {
	std::cout << "\n--- Day 19: Tractor Beam ---\n" << '\n';
	std::vector<long long int> tractor_beam_area {day_19::scan_area()};

	long long int part_1{ 0 };
	size_t limit = tractor_beam_area.size();
	for (size_t i{ 0 }; i < limit; ++i) {
		part_1 += tractor_beam_area[i];
		std::cout << (tractor_beam_area[i] == 1 ? '#' : '.');
		if (i % MAX_POS == 0 && i > 0) {
			std::cout << '\n';
		}
	}
	std::cout << '\n';

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << find_closest(100) << '\n';
}

std::vector<long long int> day_19::scan_area() {
	
	std::vector<long long int> input { intcode::get_long_programme(INPUT_FILE) };

	Intcode drone(input);

	std::vector<long long int> points_affected{ 0 };

	for (long long int i{ 0 }; i < MAX_POS; ++i) {
		for (long long j{ 0 }; j < MAX_POS; ++j) {
			points_affected.push_back(get_output(i, j));
		}
	}

	return points_affected;
}


long long int day_19::find_closest(const long long int& n) {
	
	std::vector<long long int> input { intcode::get_long_programme(INPUT_FILE) };
	Intcode drone(input);
		
	long long int a{ 0 }, b{ 1 }, c{ 2 };
	long long int x{ 1 }, y{ 0 };

	while (!all_equal_to(a, b, c, 1)) {
		a = get_output(x,y);
		b = get_output(x + n - 1, y);
		c = get_output(x, y + n - 1);
		x += (c == 0) ? 1 : 0;
		y += (b == 0) ? 1 : 0;
	};

	std::cout << "x: " << x << ", y: " << y << '\n';

	return x * 10000 + y;
}