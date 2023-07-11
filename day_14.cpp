#include "day_14.h"

using Input = std::vector<std::pair<std::string, long>>;
using Reaction = std::pair<long, Input>;

long get_factor(const long& required, const long& produced) {
	if (produced >= required) {
		return 1;
	}
	if (required % produced == 0) {
		return required / produced;
	}
	long f = required / produced;
	return f + 1;
}

long calculate_ore(const std::string& file_path) {
	std::map<std::string, Reaction> reactions;
	std::vector<std::string> input_data = helper::read_file(file_path);
	// read the file 
	for (auto& s : input_data) {
		helper::remove_all_of(s, ' ');
		helper::remove_all_of(s, '=');
		std::string product, number;
		Input input_list;
		for (size_t i{ 0 }; i < s.length(); ++i) {
			if (std::ispunct(s[i])) {
				input_list.push_back(std::make_pair(product, std::stoi(number)));
				number.clear();
				product.clear();
			}
			else if (std::isdigit(s[i])) {
				number += s[i];
			}
			else {
				product += s[i];
			}
		}
		reactions[product] = std::make_pair(std::stoi(number), input_list);
	}

	std::stack<std::pair<std::string, long>> chemical_stack;
	Reaction start = reactions["FUEL"];
	long required{ start.first };
	Input input_chemicals{ start.second };
	for (auto& i : input_chemicals) {
		i.second *= required;
		chemical_stack.push(i);
	}

	std::map<std::string, long> ore_products;
	std::map<std::string, long> remainders;

	while (!chemical_stack.empty()) {
		std::pair<std::string, long> next = chemical_stack.top();
		chemical_stack.pop();

		//std::cout << "Require " << next.second << " of " << next.first << '\n';

		if (remainders.find(next.first) != remainders.end()) {
			//std::cout << "  Remainder available: " << remainders[next.first] << '\n';
			long diff = next.second > remainders[next.first] ? remainders[next.first] : next.second;
			next.second -= diff;
			remainders[next.first] -= diff;
		}

		start = reactions[next.first];
		required = get_factor(next.second, start.first);
		long remainder = start.first * required - next.second;
		remainders[next.first] += remainder;
		//std::cout << "-> Remainder of " << next.first << ": " << remainders[next.first] << '\n';
		input_chemicals = start.second;
		for (auto& i : input_chemicals) {
			if (i.first == "ORE") {
				remainders[next.first] = 0;
				ore_products[next.first] += next.second;
				break;
			}
			i.second *= required;
			if (remainders.find(i.first) != remainders.end()) {
				long diff = i.second > remainders[i.first] ? remainders[i.first] : i.second;
				i.second -= diff;
				remainders[i.first] -= diff;
			}
			if (i.second > 0) {
				chemical_stack.push(i);
			}
		}
	};

	long ore{ 0 };
	for (const auto& [prod, quantity] : ore_products) {
		long factor{ get_factor(quantity, reactions[prod].first) };
		ore += reactions[prod].second[0].second * factor;
	}

	return ore;
}



void perform_test(const std::string& file_path, const long& expected) {
	long actual{ calculate_ore(file_path) };
	std::string result { actual == expected ? "PASS" : "FAIL" };
	std::cout << "Test Result: " << result << '\n';
	if (actual != expected) {
		std::cout << "Actual: " << actual << ". Expected: " << expected << '\n';
	}
}


void day_14::print_answers() {
	// read the file into a map


	std::cout << "\n--- Day 14: Space Stoichiometry ---\n" << '\n';
	
	perform_test("input\\test_14.txt", 31);
	perform_test("input\\test_14a.txt", 165);
	perform_test("input\\test_14b.txt", 13312);
	perform_test("input\\test_14c.txt", 180697);
	perform_test("input\\test_14d.txt", 2210736);
	std::cout << '\n';

	std::cout << "Part 1: " << calculate_ore("input\\day_14.txt") << '\n';
}