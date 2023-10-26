#include "day_15.h"

// map of positions and neighbours that serves as an adjaceney matrix
using Map = std::map < Position, std::set < Position> >;


// constants for the cardinal directions
const Position UP(0, 1);
const Position DOWN(0, -1);
const Position LEFT(-1, 0);
const Position RIGHT(1, 0);

// when declaring a const map, use .at('key') to access the values.
const std::map<Position, long long int> DIRECTIONS = { {UP, 1}, {DOWN,2}, {LEFT,3}, {RIGHT,4} };
const std::map<Position, Position> OPPOSITE_MOVE = { {UP, DOWN}, {DOWN,UP}, {LEFT,RIGHT}, {RIGHT,LEFT} };


// forward declarations
std::pair<Map, Position> find_oxygen();
int BFS_shortest_path(const Map& m, const Position& from, const Position& to);
int flood_fill(const Map& m, const Position& start);

void day_15::print_answers() {
	std::cout << "\n--- Day 15: Oxygen System ---\n" << '\n';

	std::pair<Map, Position> result = find_oxygen();
	std::cout << "Part 1: " << BFS_shortest_path(result.first, Position(0, 0), result.second) << '\n';
	std::cout << "Part 2: " << flood_fill(result.first, result.second) << '\n';
}

/*

Robot map making pseudocode.

set to hold position pointers
pointer to a position to hold the location of the oxygen

current position at 0,0


start by pushing the 4 movement directions to the stack

while the stack isn't empty do the following:
	pop the stack
	send instruction to robot
	get feedback
		0 - continue to next iteration
		update current position based on direction moved
		if not been to the current position:
			push the opposite move direction to the stack
			push the other move directions to the stack (but not opposite one)
		add neighbour relation between new and previous positions (for both)
		2 - found the oxygen:
			store the position of the oxygen.

return the map and the position of the oxygen
*/


std::pair<Map, Position> find_oxygen() {
	// Intcode robot with the input
	std::vector<long long int> input = intcode::get_long_programme("input\\day_15.txt");	
	Intcode<long long int> robot(input);

	// initialise a current position.
	Position current_pos(0, 0);
	Position oxygen_pos(0, 0);

	//initialise a stack of directions to move
	std::stack<Position> moves;
	moves.push(LEFT);
	moves.push(DOWN);
	moves.push(RIGHT);
	moves.push(UP);
	
	// map to hold an adjacency matrix to represent the graph
	Map area;

	while (!moves.empty()) {
		// get the next move and pop the stack
		Position next_move = moves.top();
		moves.pop();
		// send the instruction to the robot and run the programme.
		robot.add_input_instruction(DIRECTIONS.at(next_move));
		long long int output = robot.run_programme().back();
		//std::cout << "Moving in direction ";
		// next_move.print();
		// process output - 0 is can't move so continue to next move.
		if (output == 0) {
			//std::cout << "Hit a wall...\n";
			continue;
		}
		// std::cout << "moved to ";
		// has moved...
		// store the current position as "previous" and update the current position.
		Position previous_pos(current_pos);
		current_pos += next_move;
		//current_pos.print();

		//std::cout << "Opposite move is: ";
		//opposite_move.print();
		// check if the current position has been visited, add the positions to explore if not
		if (area.find(current_pos) == area.end()) {
			// add the opposite move to the stack to enable backtracking
			Position opposite_move = OPPOSITE_MOVE.at(next_move);
			moves.push(opposite_move);
			// now add the other directions to explore
			for (const auto& d : DIRECTIONS) {
				// don't add the opposite move for a second time.
				if (d.first != opposite_move) {
					//std::cout << "move to add is ";
					//d.first.print();
					moves.push(d.first);
				}
			}
		}
		// add positions to adjacency matrix
		area[current_pos].insert(previous_pos);
		area[previous_pos].insert(current_pos);
		if (output == 2) {
			//std::cout << "Found Oxygen.\n";
			oxygen_pos = current_pos;
		}
	}

	// default by returning the oxygen position as the origin.
	return std::make_pair(area, oxygen_pos);
}


int BFS_shortest_path(const Map& m, const Position& from, const Position& to) {
	/*
	Pseudo-code from wikipedia

	procedure BFS(G, root) is
		let Q be a queue
		label root as explored
		Q.enqueue(root)
		while Q is not empty do
			v := Q.dequeue()	
			if v is the goal then
				return v
			for all edges from v to w in G.adjacentEdges(v) do
				if w is not labeled as explored then
					label w as explored
					w.parent := v
					Q.enqueue(w)
	*/

	std::queue<Position> q;
	q.push(from);

	std::map<Position, Position> visited; // hold a reference to the visited positions and where they were visited from

	while (!q.empty()) {
		Position v = q.front();
		q.pop();
		if (v == to) {
			// reached the destination, count the steps back to the start point ("from")
			int steps{ 0 };
			Position prev = v;
			while (prev != from) {
				prev = visited[prev];
				++steps;
			}
			return steps;
		}
		for (const Position& neighbour : m.at(v)) {
			if (visited.find(neighbour) == visited.end()) {
				visited[neighbour] = v;
				q.push(neighbour);
			}
		}
	};
	return -1;
}


int flood_fill(const Map& m, const Position& start) {
	// set of positions that are already filled
	std::set<Position> flooded;
	// queue of vectors to hold the positions to check on each turn
	std::queue<std::vector<Position>> q;
	q.push({ start });
	flooded.insert(start);
	// number of steps to do the flood fill
	int steps{ 0 };
	while (!q.empty()) {
		// get the next set of positions
		std::vector<Position> next = q.front();
		q.pop();
		// for each position, get the neighbours and fill them and add them to the 
		std::vector<Position> temp;
		for (const auto& i : next) {
			for (const auto& n : m.at(i)) {
				auto result = flooded.insert(n);
				if (result.second) {
					temp.push_back(n);
				}
			}
		}
		
		if (temp.empty()) {
			break;
		}
		q.push(temp);
		++steps;
	}
	return steps;
}