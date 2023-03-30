#ifndef DAY_06
#define DAY_06

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "helper.h"

namespace day_06 {
	void print_answers();

	std::map <std::string, std::vector<std::string>> get_map(const std::vector<std::string> list, const char& c);
	int total_orbits(const std::map <std::string, std::vector<std::string>>& m, const std::string& str);
	int minimum_transfers(const std::map <std::string, std::vector<std::string>>& m, const std::string& root, const std::string& from, const std::string& to);
	bool path_to(const std::map <std::string, std::vector<std::string>>& m, std::stack<std::string>& path, const std::string& start, const std::string end);
}


#endif
