#ifndef DAY_12
#define DAY_12

#include <array>
#include <iostream>

#include "helper.h"

struct Vector3
{
	int x {};
	int y {};
	int z {};
};


namespace day_12 {

	void print_answers();

	class Moon {
	private:
		Vector3 position{};
		Vector3 velocity{};

	public:
		Moon(Vector3 p) : position(p) {}
		Vector3 get_position() const { return position; }
		void apply_gravity(const Vector3& moon_position);
		void update();
		int get_total_energy() const;

		// debug function
		void print_properties() const {
			std::cout << "pos=<x= " << position.x << ",y=" << position.y << ",z=" << position.z << ">, vel=<x=" << velocity.x << ",y=" << velocity.y << ",z=" << velocity.z << ">\n";
		}
	};

	void simulate_motion(Moon moon_list[4], const int& size);
	void move(std::array<int, 4>& positions, std::array<int, 4>& vel);
}

#endif