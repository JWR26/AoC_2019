#ifndef INTCODE
#define INTCODE

#include <cmath>

#include "helper.h"


namespace intcode {
	std::vector<int> get_programme(const std::string& path);
}


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
	std::vector<int> current_programme;
	const std::vector<int> original_programme;
	std::vector<int> input_list;
	int input_index{ 0 };
	int tick{ 0 };
	OPCODE get_opcode(const int& instruction) const;
	std::vector<MODE> get_parameter_modes(const int& instruction, const Intcode::OPCODE& opcode);
	std::vector<int>& add(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);
	std::vector<int>& multiply(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);
	std::vector<int>& input(std::vector<int>& programme, const int& pos, const int& input);
	int output(const std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);
	int jump_if_true(const std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);
	int jump_if_false(const std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);
	std::vector<int>& less_than(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);
	std::vector<int>& equals(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes);

public:
	Intcode(const std::vector<int>& p, const std::vector<int>& i = {}) : current_programme(p), original_programme(p), input_list(i) {}
	std::vector<int> run_programme();
	int run_test_diagnostic();
	void update_position(const size_t& pos, const int val);
	void update_input(const std::vector<int> i);
	void reset_programme();
	bool programme_terminated() const;
};



#endif
