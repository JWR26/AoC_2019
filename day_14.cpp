#include "day_14.h"

using Input = std::vector<std::pair<std::string, int>>;
using Reaction = std::pair<int, Input>;

int get_factor(const int& required, const int& produced) {
	if (produced >= required) {
		return 1;
	}

	if (required % produced == 0) {
		return required / produced;
	}

	int f = required / produced;
	return f + 1;
}


void day_14::print_answers() {
	// read the file into a map
	std::map<std::string, Reaction> reactions;
	std::vector<std::string> input_data = helper::read_file("input\\test_14b.txt");

	for (auto& s : input_data) {
		helper::remove_all_of(s, ' ');
		std::string product;
		std::string number;
		Input input_list;
		// build input
		size_t splitter_pos = s.find("=>");
		for (size_t i{ 0 }; i < splitter_pos; ++i) {
			if (s[i] == ',') {
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
		// get last input product
		if (!product.empty() && !number.empty()) {
			input_list.push_back(std::make_pair(product, std::stoi(number))); 
			number.clear();
			product.clear();
		}
		// get product of input
		for (size_t i{ splitter_pos + 2 }; i < s.length(); ++i) {
			if (std::isdigit(s[i])) {
				number += s[i];
			}
			else {
				product += s[i];
			}
		}
		reactions[product] = std::make_pair(std::stoi(number), input_list);
	}

	std::stack<std::pair<std::string, int>> chemical_stack;
	Reaction start = reactions["FUEL"];
	int required{ start.first };
	Input input_chemicals{ start.second };
	for (auto& i : input_chemicals) {
		i.second *= required;
		chemical_stack.push(i);
	}

	std::map<std::string, int> ore_products;
	std::map<std::string, int> remainders;

	while (!chemical_stack.empty()) {
		std::pair<std::string, int> next = chemical_stack.top();
		chemical_stack.pop();
		std::cout << "Require " << next.second << " of " << next.first << '.';
		start = reactions[next.first];
		required = get_factor(next.second, start.first);
		std::cout << "Factor: " << required << '\n';
		input_chemicals = start.second;
		for (auto& i : input_chemicals) {
			if (i.first == "ORE") {
				if (ore_products.find(next.first) != ore_products.end()) {
					ore_products[next.first] += next.second;
				}
				else {
					ore_products[next.first] = next.second;
				}
				break;
			}
			i.second *= required;
			chemical_stack.push(i);
		}
	};

	int ore{ 0 };
	for (const auto& [prod, quantity] : ore_products) {
		int factor{ get_factor(quantity, reactions[prod].first) };
		std::cout << prod << ':' << quantity << '\n';
		ore += reactions[prod].second[0].second * factor;
		std::cout << reactions[prod].second[0].second * factor << '\n';
	}

	std::cout << ore;
}