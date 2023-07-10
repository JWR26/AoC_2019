#include "day_11.h"

void day_11::print_answers() {
	std::cout << "\n--- Day 11: Space Police ---\n" << '\n';

	std::vector<long long int> input = intcode::get_long_programme("input\\day_11.txt");
	
	Robot r(input);
	r.start();

	std::cout << "Part 1: " << r.number_panels_painted() << '\n';

	r.reset();
	r.start({ 1 });

	std::cout << "Part 2:\n";

	r.draw();
}