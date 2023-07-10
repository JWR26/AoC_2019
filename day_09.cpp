#include "day_09.h"


void day_09::print_answers() {
	std::cout << "\n--- Day 9: Sensor Boost ---\n" << '\n';
	
	std::vector<long long int> input_list(1);
	
	std::vector<long long int> input = intcode::get_long_programme("input\\day_09.txt");

	Intcode<long long int> computer(input, input_list);

	std::vector<long long int> output = computer.run_programme();

	for (const auto& o : output) {
		std::cout << o << ',';
	}

	long int part_1{ 0 };
	long int part_2{ 0 };

	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';
}