#ifndef DAY_11
#define DAY_11

#include <memory>
#include <set>
#include <utility>

#include "helper.h"
#include "intcode.h"


namespace day_11 {

	void print_answers();
}



template<typename T>
class Robot {

	enum PANEL_COLOUR {
		BLACK = 0,
		WHITE = 1,
	};

	enum DIRECTION {
		LEFT,
		UP,
		RIGHT,
		DOWN,
	};

private:
	// X & Y coordinates of the robot. It starts at 0,0.
	Position pos{ Position(0,0) };
	// Direction the robot is currently facing. It starts facing up
	DIRECTION current_direction{ UP };
	// Intcode is the brain of the robot.
	std::unique_ptr<Intcode<T>> brain;

	std::set<Position> white_panels;
	std::set<Position> black_panels;

	T get_instruction() const {
		if (white_panels.find(pos) != white_panels.end()) {
			return 1;
		}
		return 0;
	}

	void process_output(const std::vector<T>& output) {
		// latest instructions will be last 2 elements in the vector
		PANEL_COLOUR c = static_cast<PANEL_COLOUR>(output[output.size() - 2]);
		paint_panel(c); 
		turn(output.back());
	}

	void move_forward() {
		//std::cout << "Moving ";
		switch (current_direction)
		{
		case DIRECTION::LEFT:
			//std::cout << "Left\n";
			pos.x -= 1;
			break;
		case DIRECTION::RIGHT:
			//std::cout << "Right\n";
			pos.x += 1;
			break;
		case DIRECTION::DOWN:
			//std::cout << "Down\n";
			pos.y -= 1;
			break;
		case DIRECTION::UP:
			//std::cout << "Up\n";
			pos.y += 1;
			break;
		default:
			break;
		}
	}
	
	void paint_panel(const PANEL_COLOUR& c) {
		if (c == PANEL_COLOUR::WHITE) {
			//std::cout << "Painting white\n";
			white_panels.insert(pos);
			auto is_black = black_panels.find(pos);
			if (is_black != black_panels.end()) {
				black_panels.erase(is_black);
			}
		}
		else {
			//std::cout << "Painting black\n";
			black_panels.insert(pos);
			auto is_white = white_panels.find(pos);
			if (is_white != white_panels.end()) {
				white_panels.erase(is_white);
			}
		}
	}

	void turn(const T& i) {
		//std::cout << "Turn instruction is: " << i << '\n';
		if (i == 0) {
			current_direction = static_cast<DIRECTION>((static_cast<T>(current_direction) + 1) % 4);
		}
		else {
			current_direction = static_cast<DIRECTION>((static_cast<T>(current_direction) + 3) % 4);
		}
	}


public:
	Robot(const std::vector<T>& i) {
		brain = std::make_unique<Intcode<T>>(i);
	}

	void start(const T& intocde_input = {0}) {
		// provide the intcode with the starting instruction '0' as all panels are black at the start
		//std::cout << "Starting Robot...\n";
		std::vector<T> input {intocde_input};
		brain->update_input(input);
		// run intcode programme
		while (!brain->programme_terminated()) {
			// run the intcode
			std::vector<T> output = brain->run_programme();
			// process its output
			process_output(output);
			// move forward
			move_forward();
			// get the panel colour under the robot & add this to the input instructions
			input.push_back(get_instruction());
			brain->update_input(input);
		}
	}

	void reset() {
		brain->reset_programme();
		pos = Position(0, 0);
		current_direction = DIRECTION::UP;
		white_panels.clear();
		black_panels.clear();
	}

	void draw()const {
		int min_x{ 0 }, min_y{ 0 }, max_x{ 0 }, max_y{ 0 };

		for (const auto& w : white_panels) {
			min_x = w.x < min_x ? w.x : min_x;
			max_x = w.x > max_x ? w.x : max_x;
			min_y = w.y < min_y ? w.y : min_y;
			max_y = w.y > max_y ? w.y : max_y;
		}

		for (const auto& w : black_panels) {
			min_x = w.x < min_x ? w.x : min_x;
			max_x = w.x > max_x ? w.x : max_x;
			min_y = w.y < min_y ? w.y : min_y;
			max_y = w.y > max_y ? w.y : max_y;
		}

		std::vector<char> panels(number_panels_painted(), ' ');

		for (const auto& w : white_panels) {
			int index{ (w.x + max_x - min_x) + w.y * (min_x - max_x)};
			if (index > panels.size() - 1) {
				panels.resize(index+1, '.');
			}
			panels[index] = '#';
		}

		std::cout << '\n';

		for (size_t i{ 0 }; i < panels.size(); ++i) {
			if (i % (min_x * -1) == 0) {
				std::cout << '\n';
			}
			std::cout << panels[i];
		}

		std::cout << '\n';
	}

	size_t number_panels_painted() const {
		return black_panels.size() + white_panels.size();
	}
};

#endif // !DAY_11
