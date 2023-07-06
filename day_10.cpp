#include "day_10.h"


int part_1 = 0;
int part_2 = 0;


int gcd(const int& a, const int& b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}


void day_10::print_answers() {
	// read data from file and store each asteroids Asteroid as a pair in a list.
	std::ifstream input("input\\day_10.txt");
	std::vector<Asteroid> asteroid_positions;
	asteroid_positions.reserve(1000);
	int x = 0, y = 0; // Asteroid coordinates
	char c;
	while (input.get(c)) {
		if (c == '#') {
			asteroid_positions.emplace_back(x, y);
		}
		if (c == '\n') {
			++y;
			x = 0;
		}
		else {
			++x;
		}
	}

	Asteroid best(0,0,0.0);

	for (const Asteroid& p : asteroid_positions) {
		int result = asteroids_detected(p, asteroid_positions);
		if (result > part_1) {
			part_1 = result;
			best = p;
		}
	}

	// remove best from the map
	asteroid_positions.erase(std::find(asteroid_positions.begin(), asteroid_positions.end(), best));
	// calculate angle to best and sort by angle.
	for (Asteroid& a : asteroid_positions) {
		a.angle_to(best);
	}
	std::sort(asteroid_positions.begin(), asteroid_positions.end(), by_angle());
	// adjust for rotations.
	double prev{ -1.0 };
	int factor{ 1 };
	for (Asteroid& a : asteroid_positions) {
		if (a.angle == prev) {
			a.angle = a.angle + factor * 360.0;
			++factor;
		}
		else {
			prev = a.angle;
			factor = 1;
		}
	}
	// resort by angle
	std::sort(asteroid_positions.begin(), asteroid_positions.end(), by_angle());
	
	part_2 = asteroid_positions[199].x * 100 + asteroid_positions[199].y;

	std::cout << "\n--- Day 10: Monitoring Station ---\n\n";
	std::cout << "Part 1: ";
	std::cout << "Best is " << best.x << ',' << best.y << " with " << part_1 << " other asteroids detected." << '\n';
	//std::cout << "The " << n << "th asteroid to be vaporized is at " << nth.first << ',' << nth.second;
	std::cout << "Part 2: " << part_2 << '\n';
}

int day_10::asteroids_detected(const Asteroid& pos, const std::vector<Asteroid>& map) {
	std::vector<std::pair<int, int>> lines_of_sight;
	for (const Asteroid& p : map) {
		// asteroid cannot see itself
		if (pos == p) {
			continue;
		}
		std::pair<int, int> los = get_line_of_sight(pos, p);
		if (std::find(lines_of_sight.begin(), lines_of_sight.end(), los) == lines_of_sight.end()) {
			lines_of_sight.push_back(los);
		}
	}
	return (int)lines_of_sight.size();
}

std::pair<int, int> day_10::get_line_of_sight(const Asteroid& from, const Asteroid& to) {
	std::pair<int, int> diff(to.x - from.x, to.y - from.y);
	if (diff.first == 0) {
		diff.second /= abs(diff.second);
	}
	else if (diff.second == 0) {
		diff.first /= abs(diff.first);
	}
	else {
		int divisor = abs(gcd(diff.first, diff.second));
		diff.first /= divisor;
		diff.second /= divisor;
	}
	
	return diff;
}
