#ifndef DAY_03
#define DAY_03

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string>
#include <map>
#include <vector>

#include "helper.h"

using Point = std::pair<int, int>;

namespace day_03 {

	void print_answers();

	std::map<Point, int> draw_wire(const std::string& path);

	int find_closest_intersection(const std::map<Point, int>& a, const std::map<Point, int>& b);
	
	int find_quickest_intersection(const std::map<Point, int>& a, const std::map<Point, int>& b);
}



#endif
