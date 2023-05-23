#include "helper.h"


std::vector<std::string> helper::read_file(const std::string& file_path) {
	std::ifstream data{ file_path };
	std::vector<std::string> all_lines;

	while (data) {
		std::string line{};
		std::getline(data, line, '\n');

		if (!line.empty()) {
			all_lines.push_back(line);
		}
	}

	return all_lines;
}


std::vector<std::string> helper::split_string(const std::string& str, const char& d) {
	std::vector<std::string> strings;
	strings.reserve(str.length());

	std::string temp;

	for (const char& c : str) {
		if (c != d) {
			temp += c;
		}
		else {
			strings.emplace_back(temp);
			temp.clear();
		}
	}

	if (!temp.empty()) {
		strings.emplace_back(temp);
	}

	return strings;
}


std::string& helper::remove_all_of(std::string& str, const char& c) {
	auto is_c = [c](char t) -> bool {return c == t; };
	str.erase(std::remove_if(str.begin(), str.end(), is_c), str.end());
	return str;
}