#ifndef INTCODE
#define INTCODE

#include <cmath>
#include <functional>

#include "helper.h"


namespace intcode {
	std::vector<int> get_programme(const std::string& path);
	std::vector<long long int> get_long_programme(const std::string& path);
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
	std::vector<T> input_list;
	T input_index{ 0 };
	T tick{ 0 };
	T relative_base{ 0 };

	OPCODE get_opcode(const T& instruction) const {
		Intcode::OPCODE opcode = static_cast<Intcode::OPCODE>(instruction % 100);
		return opcode;
	}

	void resize_programme(const T& new_size) {
		current_programme.resize(new_size + 1, 0);
	}

	T get_index(const std::vector<T>& programme, const T& pos, const T& diff, const MODE& m) {
		T index{ 0 };

		if (m == MODE::IMMEDIATE) {
			//std::cout << "Immediate Mode. ";
			index = pos + diff;
		}
		else if (m == MODE::RELATIVE) {
			index = relative_base + programme[pos + diff];
			//std::cout << "Relative Mode. ";
			//std::cout << "Delta of " << programme[pos + diff] << '\n';
		}
		else {
			//std::cout << "Position Mode. ";
			index = programme[pos + diff];
		}
		//std::cout << "Index is: " << index << '\n';

		if (index >= (T)programme.size()) {
			resize_programme(index);
		}

		return index;
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
	
	template<typename T, typename O>
	std::vector<T>& modify(std::vector<T>& programme, const T& pos, const std::vector<MODE>& modes, O op) {
		T lhs{ programme[get_index(programme, pos, 1, modes[0])] };
		T rhs{ programme[get_index(programme, pos, 2, modes[1])] };
		programme[get_index(programme, pos, 3, modes[2])] = op(lhs,rhs);

		return programme;
	}

	std::vector<T>& input(std::vector<T>& programme, const T& pos, const T& input, const std::vector<MODE>& modes) {
		programme[get_index(programme, pos, 1, modes[0])] = input;
		return programme;
	}
	
	template<typename T, typename C>
	T jump(const std::vector<T>& programme, const T& pos, const std::vector<MODE>& modes, C comp) {
		T first { programme[get_index(programme, pos, 1, modes[0])] };
		T second{ programme[get_index(programme, pos, 2, modes[1])] };

		if ( comp(first, 0) ) {
			return second - pos;
		} 

		return 3;
	}

	template<typename T, typename C>
	std::vector<T>& compare(std::vector<T>& programme, const T& pos, const std::vector<MODE>& modes, C comp) {
		T first{ programme[get_index(programme, pos, 1, modes[0])] };
		T second{ programme[get_index(programme, pos, 2, modes[1])] };

		programme[get_index(programme, pos, 3, modes[2])] = comp(first, second) ? 1 : 0;

		return programme;
	}

	void update_relative_base(const std::vector<T>& programme, const T& pos, const MODE& m) {
		T change{ programme[get_index(programme, pos, 1, m)] };
		//std::cout << "Change to relative base: " << change << '\n';
		relative_base += change;
	}

public:
	Intcode(const std::vector<T>& p, const std::vector<T>& i = {}) : current_programme(p), original_programme(p), input_list(i) {}

	std::vector<T> run_programme() {
		T limit = (T)current_programme.size();
		T delta{ 0 };

		std::vector<T> programme_output;

		for (tick; tick < limit; tick += delta) {
			Intcode::OPCODE opcode = get_opcode(current_programme[tick]);
			std::vector<Intcode::MODE> modes = get_parameter_modes(current_programme[tick], opcode);

			//std::cout << "\nInstruction " << tick << ':' << current_programme[tick] << '\n';

			switch (opcode)
			{
			case ADD:
				//std::cout << "Modify - Add...\n";
				modify(current_programme, tick, modes, std::plus<T>());
				break;
			case MULTIPLY:
				//std::cout << "Modify - Multiply...\n";
				modify(current_programme, tick, modes, std::multiplies<T>());
				break;
			case INPUT:
				// pause and wait for new input, returning the output.
				//std::cout << "Input...\n";
				if (input_index >= (T)input_list.size()) {
					return programme_output;
				}
				input(current_programme, tick, input_list[input_index], modes);
				++input_index;
				break;
			case OUTPUT:
				//std::cout << "Output...\n";
				programme_output.push_back(current_programme[get_index(current_programme, tick, 1, modes[0])]);
				break;
			case JUMP_IF_FALSE:
				//std::cout << "Jump - False...\n";
				delta = jump(current_programme, tick, modes, std::equal_to<T>());
				break;
			case JUMP_IF_TRUE:
				//std::cout << "Jump - True...\n";
				delta = jump(current_programme, tick, modes, std::not_equal_to<T>());
				break;
			case LESS_THAN:
				//std::cout << "Compare - Less than...\n";
				compare(current_programme, tick, modes, std::less<T>());
				break;
			case EQUALS:
				//std::cout << "Compare - Equals...\n";
				compare(current_programme, tick, modes, std::equal_to<T>());
				break;
			case OFFSET:
				//std::cout << "Updating relative base...\n";
				//std::cout << "Relative Base pre-update: " << relative_base << '\n';
				update_relative_base(current_programme, tick, modes[0]);
				break;
			case EXIT:
				//std::cout << "Exiting programme...\n";
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
		relative_base = 0;
	}

	bool programme_terminated() const {
		Intcode::OPCODE opcode = get_opcode(current_programme[tick]);
		return opcode == EXIT;
	}
};



#endif
