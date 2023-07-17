#include "day_16.h"

#include <fstream>

const std::array<int, 4> BASE_PHASES { 0,1,0,-1 };
const int PHASES{ 100 };

std::vector<int> test_sig_1 {1, 2, 3, 4, 5, 6, 7, 8 };

// forward declarations
std::vector<int> chars_to_ints(const std::string& path);
std::vector<int> construct_list(const std::vector<int>& list);
std::vector<int> get_pattern(const int& i);


void day_16::print_answers() {
	std::cout << "\n--- Day 16: Flawed Frequency Transmission ---\n" << '\n';

	// get FFT input from the file.
	std::vector<int> signal {chars_to_ints("input\\day_16.txt")};

	for (int i { 0 }; i < PHASES; ++i) {
		signal = construct_list(signal);
	}

	std::cout << "Part 1: ";

	for (size_t i{ 0 }; i < 8; ++i) {
		std::cout << signal[i];
	}

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

std::vector<int> construct_list(const std::vector<int>& list) {
	std::vector<int> new_list(list.size());

	for (int i{ 0 }; i < new_list.size(); ++i) {
		std::vector<int> pattern(get_pattern(i + 1));
		int sum{ 0 };
		for (int j{ 0 }; j < new_list.size(); ++j) {
			int p_index{ (j + 1) % static_cast<int>(pattern.size()) };
			sum += list[j] * pattern[p_index];
		}
		new_list[i] = abs(sum % 10);
	}

	return new_list;
}


std::vector<int> get_pattern(const int& n) {
	std::vector<int> pattern;
	for (int i{ (int)BASE_PHASES.size() - 1 }; i > -1; --i) {
		pattern.insert(pattern.begin(), n, BASE_PHASES[i]);
	}
	return pattern;
}