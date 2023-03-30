#include "day_06.h"

void day_06::print_answers() {
	std::cout << "\n--- Day 6: Universal Orbit Map ---\n" << std::endl;

	std::vector<std::string> input = helper::read_file("input\\day_06.txt");
	std::map <std::string, std::vector<std::string>> m = get_map(input, ')');

	int part_1{ 0 };

	for (const auto& k: m) {
		part_1 += total_orbits(m, k.first);
	}

	std::cout << "Part 1: " << part_1 << std::endl;

	int part_2 = minimum_transfers(m, "COM", "YOU", "SAN");

	std::cout << "Part 2: " << part_2 << std::endl;

}

std::map <std::string, std::vector<std::string>> day_06::get_map(const std::vector<std::string> list, const char& c) {
	std::map <std::string, std::vector<std::string>> m{};
	
	std::string obj_a{};
	std::string obj_b{};

	for (const std::string& str : list) {
		std::vector<std::string> objects = helper::split_string(str, c);
		obj_a = objects[0];
		obj_b = objects[1];
		if (m.find(obj_a) != m.end()) {
			m[obj_a].push_back(obj_b);
		}
		else {
			std::vector<std::string> children = { obj_b };
			m[obj_a] = children;
		}
	}

	return m;
}


int day_06::total_orbits(const std::map <std::string, std::vector<std::string>>& m, const std::string& str) {
	// counts the total orbits recursively by adding the number of direct orbits of each node in a tree structure to all of its parents.
	if (m.find(str) == m.end()) {
		return 0;
	}

	int total{ 0 };
	for (const auto& s : m.find(str)->second) {
		++total;
		total += total_orbits(m, s);
	}

	return total;
}


int day_06::minimum_transfers(const std::map <std::string, std::vector<std::string>>& m, const std::string& root, const std::string& from, const std::string& to) {
	// function that compares the paths root->from and root-> to.
	// each path is a stack where the root is at the top of the stack. compare successively the two stacks, popping off common nodes. When the top of the stacks do not match, the previously "popped" node will have been the lowest common ancestor in the tree. Count the remaining elements in each stack to find the number of transfers to get from "from"'s parent to "to"'s parent.
	std::stack<std::string> root_to;
	std::stack<std::string> root_from;
	
	// if no path is found, return -1
	if (!path_to(m, root_to, root, to)) {
		return -1;
	}

	if (!path_to(m, root_from, root, from)) {
		return -1;
	}

	while (root_to.top() == root_from.top()) {
		root_to.pop();
		root_from.pop();

		// calling top() on an empty stack will cause undefined behaviour so add a quick safety check.
		if (root_to.empty() || root_from.empty()) {
			break;
		}
	}

	return (int) (root_to.size() + root_from.size());
}


bool day_06::path_to(const std::map <std::string, std::vector<std::string>>& m, std::stack<std::string>& path, const std::string& start, const std::string end) {
	// function to find the path from a start to end in a given map "m". Returns a Boolean, indicating weather "end" was found or not.
	// the path to be updated should be passed in as a non-constant reference.
	// when the end is found, the "start" will be pushed onto the stack and trigger the exit of the recursion.
	if (m.find(start) == m.end()) {
		return false;
	}

	for (const auto& s : m.find(start)->second) {
		if (s == end) {
			path.push(start);
			return true;
		}
		// check the current "start"'s descendants for the "end" node.
		if (path_to(m, path, s, end)) {
			path.push(start);
			return true;
		}
	}

	return false;
}