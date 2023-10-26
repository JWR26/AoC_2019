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

std::vector<std::vector<char>> helper::file_to_grid(const std::string& path) {
	std::ifstream data{path};
	std::vector<std::vector<char>> grid;

	while (data) {
		std::string line{};
		std::getline(data, line, '\n');
		if (line.empty()) {
			continue;
		}
		std::vector<char> row;
		for (const char& c : line) {
			row.push_back(c);
		}

		grid.push_back(row);
	}

	return grid;
}

std::map<Position, std::vector<Position>> helper::grid_to_graph(const std::vector<std::vector<char>>& grid, const std::set<char>& exceptions) {
	std::map<Position, std::vector<Position>> graph;

	int rows{ static_cast<int>(grid.size()) };
	int cols{ static_cast<int>(grid.front().size()) };

	for (int r{ 0 }; r < rows; ++r) {
		for (int c{ 1 }; c < cols; ++c) {
			char id{ grid[r][c] };
			if (exceptions.find(id) != exceptions.end()) {
				continue;
			}
			Position n(c, r, id);

			if (exceptions.find(grid[r][c - 1]) == exceptions.end()) {
				id = grid[r][c - 1];
				Position left(c - 1, r, id);
				graph[n].push_back(left);
				graph[left].push_back(n);
			}

			if (r < 1) {
				continue;
			}

			if (exceptions.find(grid[r - 1][c]) == exceptions.end()) {
				id = grid[r - 1][c];
				Position up(c, r - 1, id);
				graph[n].push_back(up);
				graph[up].push_back(n);
			}
		}
	}

	return graph;
}

Position helper::find_position(const std::map<Position, std::vector<Position>>& graph, const char& c) {
	for (const auto& [node, neighbours] : graph) {
		if (node.id == c) {
			return node;
		}
	}

	throw std::invalid_argument("ID not found in graph.");
}

void helper::print_grid(const std::vector<std::vector<char>>& g) {
	std::cout << "Grid:\n";
	for (const auto& row : g) {
		for (const auto& c : row) {
			std::cout << c;
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void helper::print_graph(const std::map<Position, std::vector<Position>>& g) {
	std::cout << "Graph:\n";
	for (const auto& [key, value] : g) {
		std::cout << key << ": ";
		for (const auto& v : value) {
			std::cout << v << ", ";
		}
		std::cout << "\n";
	}
}