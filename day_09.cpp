#include "day_09.h"


void day_09::print_answers() {
	std::cout << "\n--- Day 9: Sensor Boost ---\n" << '\n';
	
	std::vector<long long int> input_list {1};
	
	std::vector<long long int> input = intcode::get_long_programme("input\\day_09.txt");

	Intcode<long long int> computer(input, input_list);

	std::vector<long long int> output = computer.run_programme();

	std::cout << "Part 1: " << output.back() << '\n';

	computer.reset_programme();
	computer.update_input({ 2 });
	output = computer.run_programme();

	std::cout << "Part 2: " << output.back() << '\n';
}