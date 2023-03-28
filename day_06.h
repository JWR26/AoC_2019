#ifndef DAY_06
#define DAY_06

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "helper.h"

namespace day_06 {
	void print_answers();

	std::map <std::string, std::vector<std::string>> get_map(const std::vector<std::string> list, const char& c);
	int total_orbits(const std::map <std::string, std::vector<std::string>>& m, const std::string& str, const int& i);
}


#endif
