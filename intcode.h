#ifndef INTCODE
#define INTCODE

#include <cmath>
#include <functional>

#include "helper.h"



namespace intcode {
	std::vector<int> get_programme(const std::string& path);
	std::vector<long long int> get_ll_programme(const std::string& path);
}

template <typename T>
class Intcode {

	enum OPCODE {
		ADD = 1,
		MULTIPLY = 2,
		INPUT = 3,
		OUTPUT = 4,
		JUMP_IF_TRUE = 5,
		JUMP_IF_FALSE = 6,
		LESS_THAN = 7,
		EQUALS = 8,
		OFFSET = 9,
		EXIT = 99
	};

	enum MODE {
		POSITION = 0,
		IMMEDIATE = 1,
		RELATIVE = 2
	};

private:
	std::vector<T> current_programme;
	const std::vector<T> original_programme;
	std::vector<int> input_list;
	int input_index{ 0 };
	int tick{ 0 };
	int relative_base{ 0 };

	OPCODE get_opcode(const T& instruction) const {
		Intcode::OPCODE opcode = static_cast<Intcode::OPCODE>(instruction % 100);
		return opcode;
	}

	T get_parameter(const std::vector<T>& programme, const int& pos, const int& diff, const MODE& m) {
		if (m == MODE::IMMEDIATE) {
			return programme[pos + diff];
		}
		return programme[programme[pos + diff]];
	}

	std::vector<MODE> get_parameter_modes(const T& instruction, const Intcode::OPCODE& opcode) {
		std::vector<Intcode::MODE> modes;
		int num{ 1 };

		switch (opcode) {
		case ADD:
			num = 3;
			break;
		case MULTIPLY:
			num = 3;
			break;
		case INPUT:
			num = 1;
			break;
		case OUTPUT:
			num = 1;
			break;
		case JUMP_IF_TRUE:
			num = 2;
			break;
		case JUMP_IF_FALSE:
			num = 2;
			break;
		case LESS_THAN:
			num = 3;
			break;
		case EQUALS:
			num = 3;
			break;
		default:
			break;
		}

		for (int i = 0; i < num; i++) {
			modes.push_back(static_cast<Intcode::MODE>((T)((instruction % (T)pow(10, i + 3)) / pow(10, i + 2))));
		}

		return modes;
	}
	
	std::vector<T>& add(std::vector<T>& programme, const int& pos, const std::vector<MODE>& modes) {
		T lhs{ get_parameter(programme, pos, 1, modes[0]) };
		T rhs{ get_parameter(programme, pos, 2, modes[1]) };
		if (modes[2] == MODE::POSITION) {
			programme[programme[pos + 3]] = lhs + rhs;
		}
		return programme;
	}
	
	std::vector<T>& multiply(std::vector<T>& programme, const int& pos, const std::vector<MODE>& modes) {
		T lhs{ get_parameter(programme, pos, 1, modes[0]) };
		T rhs{ get_parameter(programme, pos, 2, modes[1]) };
		programme[programme[pos + 3]] = lhs * rhs;
		return programme;
	}
	
	std::vector<T>& input(std::vector<T>& programme, const int& pos, const int& input) {
		programme[programme[pos + 1]] = input;
		return programme;
	}
	
	template<typename T, typename C>
	T jump(const std::vector<T>& programme, const int& pos, const std::vector<MODE>& modes, C comp) {
		T first { get_parameter(programme, pos, 1, modes[0]) };
		T second { get_parameter(programme, pos, 2, modes[1]) };

		if ( comp(first, 0) ) {
			return second - pos;
		} 

		return 3;
	}

	template<typename T, typename C>
	std::vector<T>& compare(std::vector<T>& programme, const int& pos, const std::vector<MODE>& modes, C comp) {
		T first{ get_parameter(programme, pos, 1, modes[0]) };
		T second{ get_parameter(programme, pos, 2, modes[1]) };

		programme[programme[pos + 3]] = comp(first, second) ? 1 : 0;

		return programme;
	}

public:
	Intcode(const std::vector<T>& p, const std::vector<T>& i = {}) : current_programme(p), original_programme(p), input_list(i) {}

	std::vector<T> run_programme() {
		int limit = (int)current_programme.size();
		int delta{ 0 };

		std::vector<T> programme_output;

		for (tick; tick < limit; tick += delta) {
			Intcode::OPCODE opcode = get_opcode(current_programme[tick]);
			std::vector<Intcode::MODE> modes = get_parameter_modes(current_programme[tick], opcode);

			switch (opcode)
			{
			case ADD:
				add(current_programme, tick, modes);
				break;
			case MULTIPLY:
				multiply(current_programme, tick, modes);
				break;
			case INPUT:
				// pause and wait for new input, returning the output.
				if (input_index >= input_list.size()) {
					return programme_output;
				}
				input(current_programme, tick, input_list[input_index]);
				++input_index;
				break;
			case OUTPUT:
				programme_output.push_back(get_parameter(current_programme, tick, 1, modes[0]));
				break;
			case JUMP_IF_FALSE:
				delta = jump(current_programme, tick, modes, std::equal_to<T>());
				break;
			case JUMP_IF_TRUE:
				delta = jump(current_programme, tick, modes, std::not_equal_to<T>());
				break;
			case LESS_THAN:
				compare(current_programme, tick, modes, std::less<T>());
				break;
			case EQUALS:
				compare(current_programme, tick, modes, std::equal_to<T>());
				break;
			case EXIT:
				if (programme_output.empty()) {
					programme_output.push_back(current_programme[0]);
				}
				return programme_output;
			default:
				break;
			}

			if (opcode != JUMP_IF_FALSE && opcode != JUMP_IF_TRUE) {
				delta = (int)modes.size() + 1;
			}
		}

		return programme_output;
	}

	T run_test_diagnostic() {
		std::vector<T> outputs = run_programme();
		size_t checks = outputs.size() - 1;
		// ensure all tests passed.
		for (size_t i{ 0 }; i < checks; ++i) {
			if (outputs[i] != 0) {
				return -1;
			}
		}
		// return test diagnostic code
		return outputs.back();
	}

	void update_position(const size_t& pos, const T val) {
		current_programme[pos] = val;
	}

	void update_input(const std::vector<T> i) {
		input_list = i;
	}

	void reset_programme() {
		current_programme = original_programme;
		input_index = 0;
		tick = 0;
	}

	bool programme_terminated() const {
		Intcode::OPCODE opcode = get_opcode(current_programme[tick]);
		return opcode == EXIT;
	}
};



#endif
