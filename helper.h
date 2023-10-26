#ifndef HELPER
#define HELPER

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Position {
	int x{}, y{};
	char id;

	// default constructor 
	Position() {}

	Position(const int& _x, const int& _y, const char& _id = ' ') : x(_x), y(_y), id(_id) {}

	Position(const Position& other) {
		x = other.x;
		y = other.y;
		id = other.id;
	}

	void print() const {
		std::cout << "Position(x,y): " << x << ',' << y << '\n';
	}

	bool operator<(const Position& other) const {
		return (x < other.x || (x == other.x && y < other.y));
	}

	bool operator==(const Position& other) const {
		return (x == other.x && y == other.y && id == other.id);
	}

	bool operator!=(const Position& other) const {
		return (x != other.x || y != other.y || id != other.id);
	}

	Position& operator=(const Position& other) {
		this->x = other.x;
		this->y = other.y;
		this->id = other.id;
		return *this;
	}

	Position& operator+=(const Position& other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Position& p) {
		os << '"' << p.id << "\" (" << p.x << ',' << p.y << ')';
		return os;
	}
};



namespace helper {

	std::vector<std::string> read_file(const std::string& file_path);

	std::vector<std::string> split_string(const std::string& str, const char& d);

	std::string& remove_all_of(std::string& str, const char& c);

	std::vector<std::vector<char>> file_to_grid(const std::string& path);

	std::map<Position, std::vector<Position>> grid_to_graph(const std::vector<std::vector<char>>& grid, const std::set<char>& exceptions);

	Position find_position(const std::map<Position, std::vector<Position>>& graph, const char& c);

	void print_grid(const std::vector<std::vector<char>>& g);

	void print_graph(const std::map<Position, std::vector<Position>>& g);
}

#endif // helper
