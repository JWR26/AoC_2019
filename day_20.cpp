#include "day_20.h"
#include "graphs.h"

void solve(const std::string& input, const std::string& expected);
graph::weighted<char> grid_to_graph(const std::vector<std::vector<char>>& grid);


void day_20::print_answers() {
	std::cout << "\n--- Day 20: Donut Maze ---\n\n";

	solve("input\\test_20a.txt", "Expected\n23 steps : AA BC DE FG ZZ\n");
	solve("input\\test_20b.txt", "Expected\n58 steps: AA AS QG BU JO ZZ\n");
	// solve("input\\day_18.txt", "Expected\n??? steps");
}

void solve(const std::string& input, const std::string& expected) {
	std::cout << "\nSolving: " << input << '\n';

	// read the file to a grid
	std::vector<std::vector<char>> grid = helper::file_to_grid(input);
	graph::weighted<char> graph = grid_to_graph(grid);
	std::cout << graph;
	// at this stage establish the "portals" these will always be a vertex with a single neighbour
	auto is_portal = [](std::vector<graph::edge<char>> _e) -> bool { return _e.size() == 1; };
	std::vector<graph::vertex<char>> portals = graph.find_vertices_if(is_portal);

	// check up, down, left, right in the grid for two characters - finding them gives the portal letters
	// store the portal letters as key, with portals as value in vector
	std::map<std::string, std::vector<graph::vertex<char>>> portal_ids;

	// loop the map, making edges between the portals
	for (const auto& [p, v] : portal_ids) {
		graph.add_edge(v, 1);
	}

	for (const auto& p : portals) {
		std::cout << p << '\n';
	}


	// connect the portals & remove single letter nodes

	// remove any dead ends ('.' with only one neighbour)


	// make the graph weighted - portal

	std::cout << expected;
}

graph::weighted<char> grid_to_graph(const std::vector<std::vector<char>>& grid) {
	graph::weighted<char> graph;

	// builds the graph but without portals

	int rows{ static_cast<int>(grid.size()) };
	
	for (int r{ 2 }; r < rows-2; ++r) {
		int columns{ static_cast<int>(grid[r].size())};
		for (int c{ 2 }; c < columns; ++c) {
			char id{ grid[r][c] };

			if (id == '.') {
				graph::vertex<char> v(c, r, id);

				if (grid[r][c - 1] == '.') {
					graph::vertex<char> n(c - 1, r, id);
					graph.add_edge(v, n, 1);
					graph.add_edge(n, v, 1);
				}

				if (grid[r - 1][c] == '.') {
					graph::vertex<char> n(c, r - 1, id);
					graph.add_edge(v, n, 1);
					graph.add_edge(n, v, 1);
				}
			}
		}
	}

	return graph;
}