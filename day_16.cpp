#include "day_16.h"

#include <fstream>

// forward declarations
std::vector<int> chars_to_ints(const std::string& path);


void day_16::print_answers() {
	std::cout << "\n--- Day 16: Flawed Frequency Transmission ---\n" << '\n';

	// get FFT input from the file.


	// declare base pattern for phases as a constant array.
	const int base_phases[]{ 0,1,0,-1 };


	// perform a phase

	// 1) construct new list of same length as input

	// new list becomes the input of the next phase

	std::cout << "Part 1: ";	
	std::cout << '\n';
	std::cout << "Part 2: " << '\n';
}


std::vector<int> chars_to_ints(const std::string& path) {
	std::ifstream input(path);
	std::vector<int> integers;
	char c;
	while (input.get(c)) {
		integers.push_back(c - '0');
	}
	return integers;
}