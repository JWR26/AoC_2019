#ifndef DAY_10
#define DAY_10

#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

struct Asteroid {
	int x, y, diff_x{ 0 }, diff_y{ 0 };
	double angle;
	
	Asteroid(int x, int y, double a = 0.0) : x(x), y(y), angle(a) {}

	void angle_to(const Asteroid& a) {
		diff_x = x - a.x;
		diff_y = y - a.y;
		angle = atan2(diff_x, diff_y) * 180.0 / 3.14159265;
		if (angle < 0) {
			angle = angle * -1 + 180.0;
		}
	}

	void print() const {
		std::cout << "X: " << x << "; Y: " << y << "; Angle: " << angle << '\n';
	}

	bool operator == (const Asteroid& a) const {
		return (x == a.x && y == a.y && angle == a.angle);
	}
};

struct by_angle {
	bool operator () (const Asteroid& a1, const Asteroid& a2) {
		if (a1.angle == a2.angle) {
			return (abs(a1.diff_x) + abs(a1.diff_y) < abs(a2.diff_x) + abs(a2.diff_y));
		}
		return (a1.angle < a2.angle);
	}
};

namespace day_10 {

	void print_answers();
	int asteroids_detected(const Asteroid& pos, const std::vector<Asteroid>& map);
	std::pair<int, int> get_line_of_sight(const Asteroid& from, const Asteroid& to);
}


#endif // !DAY_10
