#include "day_13.h"

void day_13::print_answers() {
	std::cout << "\n--- Day 13: Care Package ---\n" << '\n';

	std::vector<long long int> input = intcode::get_long_programme("input\\day_13.txt");

	Intcode<long long int> computer(input);

	std::vector<long long int> output = computer.run_programme();

	int part_1{ 0 };

	for (size_t i{ 2 }; i < output.size(); i += 3) {
		if (output[i] == 2) {
			++part_1;
		}
	}
	
	std::cout << "Part 1: " << part_1 << '\n';

	computer.reset_programme();
	computer.update_position(0, 2);

	std::vector<long long int> joystick_input;

	while (!computer.programme_terminated()) {
		output = computer.run_programme();
		long long int ball_pos{ 0 }, paddle_pos{ 0 };
		for (size_t i{ 2 }; i < output.size(); i += 3) {
			if (output[i] == 4) {
				ball_pos = output[i - 2];
			}
			else if (output[i] == 3) {
				paddle_pos = output[i - 2];
			}
		}
		joystick_input.push_back(ball_pos - paddle_pos);
		computer.update_input(joystick_input);
	};

	long long int part_2{ 0 };

	for (size_t i{ 0 }; i < output.size(); i += 3) {
		if (output[i] == -1 && output[i+1] == 0) {
			part_2 = output[i + 2];
			break;
		}
	}

	std::cout << "Part 2: " << part_2 << '\n';

}