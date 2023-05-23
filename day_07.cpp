#include "day_07.h"

void day_07::print_answers() {
	std::cout << "\n--- Day 7: Amplification Circuit ---\n\n";

	std::vector<int> programme = intcode::get_programme("input\\day_07.txt");
	/* Test answers: 
	07a: 43210 from 4,3,2,1,0
	07b: 54321 from 0,1,2,3,4
	07c: 65210 from 1,0,4,3,2 
	07d: 139629729 from 9,8,7,6,5
	07e: 18216 from 9,7,8,5,6*/
	int phases[]{ 0,1,2,3,4 };
	int largest_output_signal{ 0 };

	// cycle through permutations of phase_settings
	do {
		int output{ 0 };
		for (size_t i = 0; i < 5; ++i) {
			std::vector<int> inputs{ phases[i], output };
			Intcode computer(programme, inputs);
			output = computer.run_programme()[0];
		}
		// check amp E's output to see if it is the largest
		if (output > largest_output_signal) {
			largest_output_signal = output;
		}
	} while (std::next_permutation(phases, phases + 5));

	std::cout << "Part 1: " << largest_output_signal << '\n';

	// new phase settings
	for (int i{ 0 }; i < 5; ++i) {
		phases[i] = 5 + i;
	}

	// cycle through permutations of phase_settings
	do {
		int output{ 0 };

		std::vector<int> input_a{ phases[0] };
		Intcode Amp_A(programme, input_a);
		std::vector<int> input_b{ phases[1] };
		Intcode Amp_B(programme, input_b);
		std::vector<int> input_c{ phases[2] };
		Intcode Amp_C(programme, input_c);
		std::vector<int> input_d{ phases[3] };
		Intcode Amp_D(programme, input_d);
		std::vector<int> input_e{ phases[4] };
		Intcode Amp_E(programme, input_e);

		while (!Amp_E.programme_terminated()) {
			input_a.push_back(output);
			Amp_A.update_input(input_a);
			output = Amp_A.run_programme().back();
			input_b.push_back(output);
			Amp_B.update_input(input_b);
			output = Amp_B.run_programme().back();
			input_c.push_back(output);
			Amp_C.update_input(input_c);
			output = Amp_C.run_programme().back();
			input_d.push_back(output);
			Amp_D.update_input(input_d);
			output = Amp_D.run_programme().back();
			input_e.push_back(output);
			Amp_E.update_input(input_e);
			output = Amp_E.run_programme().back();
		}
		// check amp E's output to see if it is the largest
		if (output > largest_output_signal) {
			largest_output_signal = output;
		}
	} while (std::next_permutation(phases, phases + 5));

	std::cout << "Part 2: " << largest_output_signal << '\n';
}