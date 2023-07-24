#include "day_16.h"

#include <fstream>

const std::array<int, 4> BASE_PHASES { 0,1,0,-1 };
const int PHASES{ 100 };

std::vector<int> test_sig_1 {1, 2, 3, 4, 5, 6, 7, 8 };

// forward declarations
std::vector<int> chars_to_ints(const std::string& path);
std::vector<int> construct_list(const std::vector<int>& list, const int& start = 0, const int& multiplier = 1);
std::vector<int> get_pattern(const int& i);


void day_16::print_answers() {
	std::cout << "\n--- Day 16: Flawed Frequency Transmission ---\n" << '\n';

	// get FFT input from the file.
	std::vector<int> signal {chars_to_ints("input\\day_16.txt")};

	std::cout << "Part 1: ";

	std::vector<int> part_1(signal);
	
	for (int i{ 0 }; i < PHASES; ++i) {
		part_1 = construct_list(part_1);
	}
	
	for (size_t i{ 0 }; i < 8; ++i) {
		std::cout << part_1[i];
	}
	std::cout << '\n';

	std::cout << "Part 2: ";

	int message_offset{ 0 };

	for (size_t i{ 0 }; i < 8; ++i) {
		message_offset *= 10;
		message_offset += signal[i];
	}

	signal = construct_list(signal, message_offset, 10000);
	for (int i{ 1 }; i < PHASES; ++i) {
		signal = construct_list(signal, message_offset);
	}

	std::cout << '\n';

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

// add start and multiplication factor
std::vector<int> construct_list(const std::vector<int>& list, const int& start, const int& multiplier) {
	std::vector<int> new_list(list.size() * multiplier, 0);

	int limit = static_cast<int>(new_list.size()) * multiplier;

	for (int i{ start }; i < limit; ++i) {
		// pattern only needed for first half of list, second half is just 1.
		std::vector<int> pattern({ 1 });
		if (i < limit / 2) {
			pattern = get_pattern(i + 1);
		}
		int sum{ 0 };
		int old_limit = static_cast<int>(list.size());
		for (int j{ i }; j < limit; ++j) {
			int p_index{ (j + 1) % static_cast<int>(pattern.size()) };
			sum += list[j%old_limit] * pattern[p_index];
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