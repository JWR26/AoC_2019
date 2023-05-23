#include "day_12.h"

uint64_t gcd(const uint64_t& a, const uint64_t& b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

uint64_t lcm(const uint64_t& a, const uint64_t& b) {
	return a * b / gcd(a, b);
}

Vector3& operator += (Vector3& lhs, const Vector3& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

void day_12::Moon::apply_gravity(const Vector3& moon_position) {
	if (position.x != moon_position.x) {
		velocity.x += position.x < moon_position.x ? 1 : -1;
	}
	if (position.y != moon_position.y) {
		velocity.y += position.y < moon_position.y ? 1 : -1;
	}
	if (position.z != moon_position.z) {
		velocity.z += position.z < moon_position.z ? 1 : -1;
	}
}

void day_12::Moon::update() {
	position += velocity;
}

int day_12::Moon::get_total_energy() const {
	int potential = abs(position.x) + abs(position.y) + abs(position.z);
	int kinetic = abs(velocity.x) + abs(velocity.y) + abs(velocity.z);
	//std::cout << "pot: " << potential << "; kin: " << kinetic << "; total: " << potential * kinetic << ";\n";
	return potential * kinetic;
}

void day_12::print_answers() {
	Moon list[4]{
		Moon(Vector3{ 13, -13, -2 }),
		Moon(Vector3{ 16, 2, -15 }),
		Moon(Vector3{ 7, -18, -12 }),
		Moon(Vector3{ -3, -8, -8 }),
	};

	const std::array<int, 4>  MOON_X{ 13, 16, 7, -3 };
	const std::array<int, 4>  MOON_Y{ -13, 2, -18, -8 };
	const std::array<int, 4>  MOON_Z{ -2, -15, -12, -8 };

	std::array<int, 4> moon_x = MOON_X;
	std::array<int, 4> moon_y = MOON_Y;
	std::array<int, 4> moon_z = MOON_Z;

	const std::array<int, 4> VEL_X{}, VEL_Y{}, VEL_Z{};
	std::array<int, 4> vel_x{}, vel_y{}, vel_z{};

	int steps{ 0 };
	int part_1 = 0;
	uint64_t part_2{};
	uint64_t  x_interval{0}, y_interval{0}, z_interval{0};

	do {	
		simulate_motion(list, 4);
		++steps;
		++x_interval;
		move(moon_x, vel_x);
		++y_interval;
		move(moon_y, vel_y);
		++z_interval;
		move(moon_z, vel_z);
	} while (steps < 1000);


	for (int i{ 0 }; i < 4; ++i) {
		part_1 += list[i].get_total_energy();
		list[i].print_properties();
		std::cout << moon_x[i] << ',' << moon_y[i] << ',' << moon_z[i] << ';' << vel_x[i] << ',' << vel_y[i] << ',' << vel_z[i] << '\n';
	}

	while (true) {
		if (moon_x == MOON_X && vel_x == VEL_X) {
			break;
		}
		++x_interval;
		move(moon_x, vel_x);
	}

	while (true) {
		if (moon_y == MOON_Y && vel_y == VEL_Y) {
			break;
		}
		++y_interval;
		move(moon_y, vel_y);
	}

	while (true) {
		if (moon_z == MOON_Z && vel_z == VEL_Z) {
			break;
		}
		++z_interval;
		move(moon_z, vel_z);
	}

	std::cout << x_interval << ',' << y_interval << ',' << z_interval << '\n';

	for (int i{ 0 }; i < 4; ++i) {
		std::cout << moon_x[i] << ',' << moon_y[i] << ',' << moon_z[i] << ';' << vel_x[i] << ',' << vel_y[i] << ',' << vel_z[i] << '\n';
	}

	part_2 = lcm(lcm(x_interval, y_interval), z_interval);
	
	std::cout << "\n--- Day 12: The N-Body Problem ---\n\n";
	std::cout << "Part 1: " << part_1 << '\n';
	std::cout << "Part 2: " << part_2 << '\n';
}


void day_12::simulate_motion(Moon moon_list[4], const int& size) {
	for (int i{ 0 }; i < size; ++i) {
		for (int j{ i + 1 }; j < size; ++j) {
			moon_list[i].apply_gravity(moon_list[j].get_position());
			moon_list[j].apply_gravity(moon_list[i].get_position());
		}
		moon_list[i].update();
		//moon_list[i].print_properties();
	}
}


void day_12::move(std::array<int, 4>& positions, std::array<int, 4>& vel) {
	for (size_t i{ 0 }; i < positions.size(); ++i) {
		for (size_t j{ i + 1 }; j < positions.size(); ++j) {
			if (positions[i] != positions[j]) {
				vel[i] += positions[i] < positions[j] ? 1 : -1;
				vel[j] += positions[j] < positions[i] ? 1 : -1;
			}
		}
		positions[i] += vel[i];
	}
}

 