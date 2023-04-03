#include "day_02.h"

void day_02::print_answers() {
	std::cout << "\n--- Day 2: 1202 Program Alarm ---\n" << std::endl;

	std::vector<int> input = intcode::get_programme("input\\day_02.txt");

	Intcode computer(input);
	// update position 1 with 12 and 2 with 2
	computer.update_position(1, 12);
	computer.update_position(2, 2);

	std::cout << "Part 1: " << computer.run_programme()[0] << '\n';

	computer.reset_programme();

	int noun{ 0 }, verb{ 0 };

	for (int i = 1; i < 100; ++i) {
		for (int j = 1; j < 100; ++j) {
			computer.update_position(1, i);
			computer.update_position(2, j);
			if (computer.run_programme()[0] == 19690720) {
				noun = i;
				verb = j;
			}
			computer.reset_programme();
		}
	}

	std::cout << "Part 2: " << product(noun, verb) << std::endl;
}


int day_02::product(const int& noun, const int& verb) {
	return 100 * noun + verb;
}