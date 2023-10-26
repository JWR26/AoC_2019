#ifndef DAY_22
#define DAY_22

#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

#include "helper.h"

struct path_result {
	std::map<Position, Position> path;
	int vertex_visited{ 0 };
	int steps{ 0 };
};

namespace day_18 {
	void print_answers();
	void solve(const std::string& input, const std::string& expected_result);
	std::set<char> find_keys(const std::map<Position, std::vector<Position>>& graph);
	path_result bredth_first_search(const std::map<Position, std::vector<Position>>& graph, const Position& start, const std::set<char> keys);

}


#endif