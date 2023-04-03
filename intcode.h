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
		EXIT = 99
	};
	enum MODE {
		POSITION = 0,
		IMMEDIATE = 1
	};

private:
	std::vector<int> current_programme;
	const std::vector<int> original_programme;
	OPCODE get_opcode(const int& instruction);
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
	Intcode(const std::vector<int>& p) : current_programme(p), original_programme(p) {}
	std::vector<int> run_programme(const int& programme_input = 0);
	std::pair<bool, int> run_test_diagnostic(const int& programme_input);
	void update_position(const size_t& pos, const int val);
	void reset_programme();
};



#endif
