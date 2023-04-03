#include "day_05.h"

void day_05::print_answers() {
	std::cout << "\n--- Day 5: Sunny with a Chance of Asteroids ---\n" << std::endl;

	std::vector<int> input = intcode::get_programme("input\\day_05.txt");

	Intcode computer(input);
	std::pair<bool, int> test_result = computer.run_test_diagnostic(1);

	std::cout << "Part 1: " << test_result.second << '\n';

	computer.reset_programme();
	test_result = computer.run_test_diagnostic(5);

	std::cout << "Part 2: " << test_result.second << std::endl;
}