#ifndef DAY_02
#define DAY_02

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace day_02 {
	void print_answers();
	std::vector<int> get_programme(const std::string& path);
	std::vector<int> update_programme(std::vector<int>& original, const int& n, const int& v);
	int product(const int& noun, const int& verb);
}



#endif

