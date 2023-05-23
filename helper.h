#ifndef HELPER
#define HELPER

#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace helper {

	std::vector<std::string> read_file(const std::string& file_path);

	std::vector<std::string> split_string(const std::string& str, const char& d);

	std::string& remove_all_of(std::string& str, const char& c);

}


#endif // helper
