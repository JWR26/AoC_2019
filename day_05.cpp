#include "day_05.h"

void day_05::print_answers() {
	std::cout << "\n--- Day 5: Sunny with a Chance of Asteroids ---\n" << std::endl;

	std::vector<int> input = intcode::get_programme("input\\day_05.txt");

	
	std::vector<int> user_input { 1 };
	Intcode computer(input, user_input);
	int test_result = computer.run_test_diagnostic();

	std::cout << "Part 1: " << test_result << '\n';

	computer.reset_programme();
	user_input[0] = 5;
	computer.update_input(user_input);
	test_result = computer.run_test_diagnostic();

	std::cout << "Part 2: " << test_result << '\n';
}