#include "intcode.h"


std::vector<int> intcode::get_programme(const std::string& path) {
	std::ifstream data{ path };
	std::vector<int> ints;
	ints.reserve(500); // arbitrary number bigger than the list

	while (data) {
		std::string line{};
		std::getline(data, line, ',');

		if (!line.empty()) {
			int mass = std::stoi(line);
			ints.emplace_back(mass);
		}
	}

	return ints;
}


Intcode::OPCODE Intcode::get_opcode(const int& instruction) {
	Intcode::OPCODE opcode = static_cast<Intcode::OPCODE>(instruction%100);
	return opcode;
}


std::vector<Intcode::MODE> Intcode::get_parameter_modes(const int& instruction, const Intcode::OPCODE& opcode) {
	std::vector<Intcode::MODE> modes;
	int num{ 1 };

	switch (opcode)
	{
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

	//std::cout << "Parameter modes are: ";
	for (int i = 0; i < num; i++) {
		modes.push_back(static_cast<Intcode::MODE>((int) ((instruction % (int)pow(10, i + 3)) / pow(10, i + 2))));
		//std::cout << (int) ((instruction % (int)pow(10, i + 3)) / pow(10, i + 2)) << ' ';
	}
	//std::cout << '\n';

	return modes;
}


std::vector<int>& Intcode::add(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	int lhs{ 0 };
	//std::cout << "Addition : \n";
	if (modes[0] == IMMEDIATE) {
		//std::cout << "Immediate parameter 1: " << programme[pos + 1] << " at position " << pos + 1 << '\n';
		lhs = programme[pos + 1];
	} 
	else {
		//std::cout << "Position parameter 1: " << programme[programme[pos + 1]] << " at position " << programme[pos + 1] << '\n';
		lhs = programme[programme[pos + 1]];
	} 
	//std::cout << "LHS is: " << lhs << '\n';
	int rhs{ 0 };
	if (modes[1] == IMMEDIATE) {
		//std::cout << "Immediate parameter 2: " << programme[pos + 2] << " at position " << pos + 2 << '\n';
		rhs = programme[pos + 2];
	}
	else {
		//std::cout << "Position parameter 2: " << programme[programme[pos + 2]] << " at position " << programme[pos + 2] << '\n';
		rhs = programme[programme[pos + 2]];
	}
	//std::cout << "RHS is: " << rhs << '\n';

	if (modes[2] == POSITION) {
		//std::cout << "Result of addition is: " << lhs + rhs << " stored at: " << programme[pos + 3] <<'\n';
		programme[programme[pos + 3]] = lhs + rhs;
	}

	return programme;
}


std::vector<int>& Intcode::multiply(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	int result{ 0 };
	if (modes[0] == IMMEDIATE) {
		result = programme[pos + 1];
	}
	else {
		result = programme[programme[pos + 1]];
	}

	if (modes[1] == IMMEDIATE) {
		result *= programme[pos + 2];
	}
	else {
		result *= programme[programme[pos + 2]];
	}

	programme[programme[pos + 3]] = result;

	return programme;
}


std::vector<int>& Intcode::input(std::vector<int>& programme, const int& pos, const int& input) {
	//std::cout << "Input Command: Storing " << input << " at address " << programme[pos + 1] << '\n';
	programme[programme[pos + 1]] = input;
	return programme;
}


int Intcode::output(const std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	//std::cout << "Output of: " << programme[programme[pos + 1]] << " from position " << programme[pos + 1] << '\n';
	if (modes[0] == IMMEDIATE) {
		return programme[pos + 1];
	}
	return programme[programme[pos + 1]];
}


int Intcode::jump_if_true(const std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	//std::cout << "Jump-if-true" << '\n';
	int first = modes[0] == IMMEDIATE ? programme[pos + 1] : programme[programme[pos + 1]];
	int second = modes[1] == IMMEDIATE ? programme[pos + 2] : programme[programme[pos + 2]];

	int jump_value = first != 0 ? second - pos : 3;

	//std::cout << "First: " << first << '\n' << "Second: " << second << '\n' << "Jump Value: " << jump_value << '\n';
	
	return jump_value;
}


int Intcode::jump_if_false(const std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	int first = modes[0] == IMMEDIATE ? programme[pos + 1] : programme[programme[pos + 1]];
	int second = modes[1] == IMMEDIATE ? programme[pos + 2] : programme[programme[pos + 2]];
	int jump_value = first == 0 ? second - pos : 3;

	return jump_value;
}


std::vector<int>& Intcode::less_than(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	int first = modes[0] == IMMEDIATE ? programme[pos + 1] : programme[programme[pos + 1]];
	int second = modes[1] == IMMEDIATE ? programme[pos + 2] : programme[programme[pos + 2]];

	programme[programme[pos + 3]] = (first < second) ? 1 : 0;

	return programme;
}


std::vector<int>& Intcode::equals(std::vector<int>& programme, const int& pos, const std::vector<MODE>& modes) {
	int first = modes[0] == IMMEDIATE ? programme[pos + 1] : programme[programme[pos + 1]];
	int second = modes[1] == IMMEDIATE ? programme[pos + 2] : programme[programme[pos + 2]];

	programme[programme[pos + 3]] = (first == second) ? 1 : 0;

	return programme;
}


std::vector<int> Intcode::run_programme(const int& programme_input) {
	int limit = (int) current_programme.size();
	int delta{ 0 };

	std::vector<int> programme_output;

	for (int i = 0; i < limit; i += delta) {
		Intcode::OPCODE opcode = get_opcode(current_programme[i]);
		//std::cout << "Opcode: " << current_programme[i] << '\n';
		std::vector<Intcode::MODE> modes = get_parameter_modes(current_programme[i], opcode);

		//std::cout << "Instruction " << i << " -> ";

		switch (opcode)
		{
		case ADD:
			add(current_programme, i, modes);
			break;
		case MULTIPLY:
			multiply(current_programme, i, modes);
			break;
		case INPUT:
			input(current_programme, i, programme_input);
			break;
		case OUTPUT:
			programme_output.push_back(output(current_programme, i, modes));
			break;
		case JUMP_IF_FALSE:
			delta = jump_if_false(current_programme, i, modes);
			break;
		case JUMP_IF_TRUE:
			delta = jump_if_true(current_programme, i, modes);
			break;
		case LESS_THAN:
			less_than(current_programme, i, modes);
			break;
		case EQUALS:
			equals(current_programme, i, modes);
			break;
		case EXIT:
			//std::cout << "Exit programme at instruction " << i <<'\n';
			if (programme_output.empty()) {
				programme_output.push_back(current_programme[0]);
			}
			return programme_output;
		default:
			break;
		}
		//std::cout << '\n';

		if (opcode != JUMP_IF_FALSE && opcode != JUMP_IF_TRUE) {
			delta = (int)modes.size() + 1;
		}
	}

	return programme_output;
}


std::pair<bool, int> Intcode::run_test_diagnostic(const int& programme_input) {
	std::pair<bool, int> result(true, programme_input);

	std::vector<int> outputs = run_programme(programme_input);

	int checks = (int) outputs.size() - 1;

	for (int i = 0; i < checks; ++i) {
		if (outputs[i] != 0) {
			//std::cout << "Result " << i << ": " << outputs[i] << " [TEST FAILED] " << '\n';;
			result.first = false;
		}
	}

	result.second = outputs.back();

	return result;
}


void Intcode::update_position(const size_t& pos, const int val) {
	current_programme[pos] = val;
}


void Intcode::reset_programme() {
	current_programme = original_programme;
}