#include "day_22.h"

void day_22::print_answers() {
	std::cout << "\n--- Day 22: Slam Shuffle ---\n" << std::endl;
	// start deck of cards
	const long long int N{ 10007 };
	std::vector<long long int> deck;
	for (long long int i = 0; i < N; ++i) {
		deck.push_back(i);
	}

	// det input
	std::vector<std::string> input = helper::read_file("input\\day_22.txt");

	// define regex patterns

	std::regex cut("cut ");
	std::regex increment("increment ");
	std::smatch sm;

	// loop over input and perform appropriate action;
	for (const auto& i : input) {
		if (std::regex_search(i, sm, increment)) {
			long long int n = std::stoi(sm.suffix().str());
			
			std::vector<long long int> updated(N);
			long long int index{ 0 };
			for (const long long int& c : deck) {
				updated[index] = c;
				index += n;
				index %= deck.size();
			}

			deck = updated;

			continue;
		}

		if (std::regex_search(i, sm, cut)) {
			long long int n = std::stoi(sm.suffix().str());
			long long int index = static_cast<long long int>((deck.size() + n) % deck.size());
			std::vector<long long int> updated(deck.begin() + index, deck.end());
			for (long long int j = 0; j < index; ++j) {
				updated.push_back(deck[j]);
			}
			deck = updated;
			continue;
		}
		std::reverse(deck.begin(), deck.end());
	}


	const auto& it = std::find(deck.begin(), deck.end(), 2019);
	std::cout << "Part 1: " << it - deck.begin() << '\n';
}