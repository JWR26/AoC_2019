#include "day_17.h"


void day_17::print_answers() {
	std::cout << "\n--- Day 17: Set and Forget ---\n" << '\n';

	// get the scaffold
	std::vector<long long int> input = intcode::get_long_programme("input\\day_17.txt");
	Intcode<long long int> computer(input);
	std::vector<long long int> output = computer.run_programme();
	
	// find columns of scaffold
	int columns{ 0 };
	while (output[columns] != 10) {
		++columns;
	}

	//for (const auto& i : output) {
	//	std::cout << (char)i;
	//}
	int rows{ (int)output.size() / columns };

	// iterate over the scaffold checking for intersections, increasing the alignment parameter sum when one is found.
	long long int alignment_parameters_sum{ 0 };

	for (int i{ 1 }; i < rows-1; ++i) {
		for (int j{ 1 }; j < columns-1; ++j) {
			int s{ (i * columns) + j + i };
			if (output[s] != 35) {
				continue;
			}
			// get the neighbour indices 
			int up{ s - columns - 1 };
			int left{ s - 1 };
			int down{ s + columns + 1};
			int right{ s + 1 };
			// now check all neighbours are scaffolds
			if (output[up] == 35 && output[left] == 35 && output[down] == 35 && output[right] == 35 ) {
				//std::cout << i << ',' << j << '\n';
				alignment_parameters_sum += (i * j);
			}
		}
	}

	std::cout << "Part 1: " << alignment_parameters_sum << '\n';
	std::cout << "Part 2: " << '\n';
}