#ifndef DAY_01
#define DAY_01

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace day_01 {

	void print_answers();

	std::vector<int> get_module_masses(std::string path);

	int fuel_for_module(int mass);

	int fuel_for_module_and_fuel(int mass);

}


#endif
