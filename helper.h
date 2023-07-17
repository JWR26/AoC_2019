#ifndef HELPER
#define HELPER

#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace helper {

	std::vector<std::string> read_file(const std::string& file_path);

	std::vector<std::string> split_string(const std::string& str, const char& d);

	std::string& remove_all_of(std::string& str, const char& c);

}


struct Position {
	int x, y;

	// default constructor 
	Position() {}

	Position(const int& _x, const int& _y) : x(_x), y(_y) {}

	Position(const Position& other) {
		x = other.x;
		y = other.y;
	}

	void print() const {
		std::cout << "Position(x,y): " << x << ',' << y << '\n';
	}

	bool operator<(const Position& other) const {
		return (x < other.x || (x == other.x && y < other.y));
	}

	bool operator==(const Position& other) const {
		return (x == other.x && y == other.y);
	}

	bool operator!=(const Position& other) const {
		return (x != other.x || y != other.y);
	}

	Position& operator=(const Position& other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Position& operator+=(const Position& other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

};

#endif // helper
