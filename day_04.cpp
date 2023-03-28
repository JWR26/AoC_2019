#include "day_04.h"

void day_04::print_answers() {
	std::cout << "\n--- Day 4: Secure Container ---\n" << std::endl;

	int low{ 245318 };
	int high{ 765747 };

	std::vector<int> passwords;
	std::vector<int> new_passwords;

	for (int i = low; i <= high; i++) {
		if (has_adjacent_digits(i) && always_increasing(i)) {
			passwords.push_back(i);
			if (check_larger_groups(i)) {
				new_passwords.push_back(i);
			}
		}
	}

	std::cout << "Part 1: " << passwords.size() << std::endl;

	std::cout << "Part 2: " << new_passwords.size() << std::endl;
}

bool day_04::has_adjacent_digits(const int& i) {
	int temp(i);
	int digit = temp % 10;

	while (temp > 0) {
		temp /= 10;
		int next = temp % 10;
		if (next == digit) {
			return true;
		}
		digit = next;
	}
	
	return false;
}


bool day_04::always_increasing(const int& i) {
	int temp(i);
	int digit = temp % 10;

	while (temp > 0) {
		temp /= 10;
		int next = temp % 10;
		if (next > digit) {
			return false;
		}
		digit = next;
	}

	return true;
}


bool day_04::check_larger_groups(const int& i) {
	int temp(i);
	int digit = temp % 10;
	int num_adjacent = 0;

	while (temp > 0) {
		temp /= 10;
		int next = temp % 10;
		if (next == digit) {
			++num_adjacent;
		}
		else if (num_adjacent == 1) {
			return true;
		}
		else {
			num_adjacent = 0;
		}
		digit = next;
	}

	return false;
}
