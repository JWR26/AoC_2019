#include "day_18.h"

using UnweightedGraph = std::map<Position, std::vector<Position>>;
using WeightedGraph = std::map < Position, std::vector<std::pair<Position, int>>>;

void print_keys(const std::set<char>& keys) {
	std::cout << "Keys: ";
	for (const auto& k : keys) {
		std::cout << k << ' ';
	}
	std::cout << '\n';
}

void print_graph_info(const UnweightedGraph& graph) {
	std::cout << "Graph Order: " << graph.size() << '\n';
	size_t size{};
	for (const auto& [k, v] : graph) {
		size += v.size();
	}
	std::cout << "Graph Size: " << size << '\n';
}

void print_graph_info(const WeightedGraph& graph) {
	std::cout << "Graph Order: " << graph.size() << '\n';
	size_t size{};
	for (const auto& [k, v] : graph) {
		size += v.size();
	}
	std::cout << "Graph Size: " << size << '\n';
}

void print_graph(const WeightedGraph& graph) {
	std::cout << "Graph\n";
	for (const auto& [k, v] : graph) {
		std::cout << k << ':';
		for (const auto& n : v) {
			std::cout << ' ' << n.first << '[' << n.second << ']';
		}
		std::cout << '\n';
	}
}

UnweightedGraph remove_dead_ends(const UnweightedGraph& graph) {
	UnweightedGraph new_graph(graph);
	
	auto dead_end = [](const UnweightedGraph& g) {
		for (auto it = g.begin(); it != g.end(); ++it) {
			if (it->second.size() == 1 && !islower(it->first.id) && it->first.id != '@') {
				return it;
			}
		}
		return g.end();
	};

	for (auto it = dead_end(new_graph); it != new_graph.end(); it = dead_end(new_graph)) {
		Position p = it->first;
		// std::cout << "removing dead end at: " << p << '\n';
		auto index = std::find(new_graph[it->second.front()].begin(), new_graph[it->second.front()].end(), p);
		if (index != new_graph[it->second.front()].end()) {
			new_graph[it->second.front()].erase(index);
		}
		new_graph.erase(it);
	}

	return new_graph;
}

WeightedGraph make_weighted(const UnweightedGraph& graph) {
	WeightedGraph w_graph;
	for (const auto& [k, v] : graph) {
		for (const auto& p : v) {
			w_graph[k].push_back(std::make_pair(p, 1));
		}
	}
	return w_graph;
}

WeightedGraph& remove_bridges(WeightedGraph& w_graph) {
	// loop the graph moving to next node with two neighbours
	// lambda helper for finding the next bridge
	auto next_bridge = [](const WeightedGraph& g) {
		for (auto it = g.begin(); it != g.end(); ++it) {
			if (it->second.size() == 2 && it->first.id == '.') {
				return it;
			}
		}
		return g.end();
	};
	// lambda helper for finding an iterator to a position
	auto find_pos = [](const std::vector<std::pair<Position, int>>& v, const Position& p) {
		for (auto it = v.begin(); it != v.end(); ++it) {
			if (it->first == p) {
				return it;
			}
		}
		return v.end();
	};

	for (auto it = next_bridge(w_graph); it != w_graph.end(); it = next_bridge(w_graph)) {
		std::pair<Position, int> a = it->second.front();
		std::pair<Position, int> b = it->second.back();
		// join up a & b
		int steps = a.second + b.second;
		w_graph[a.first].push_back(std::make_pair(b.first, steps));
		w_graph[b.first].push_back(std::make_pair(a.first, steps));
		// remove it from a and b neighbours
		w_graph[a.first].erase(find_pos(w_graph[a.first], it->first));
		w_graph[b.first].erase(find_pos(w_graph[b.first], it->first));
		// remove it from the graph
		w_graph.erase(it);
	}

	return w_graph;
}

path_result bredth_first_search(const WeightedGraph& graph, const Position& start, const std::set<char> keys);

void day_18::print_answers() {
	std::cout << "\n--- Day 18: Many-Worlds Interpretation ---\n\n";

	solve("input\\test_18a.txt", "Expected\n8 steps : a b\n");
	solve("input\\test_18b.txt", "Expected\n86 steps: a b c d e f\n");
	solve("input\\test_18c.txt", "Expected\n132 steps: b a c d f e g\n");
	solve("input\\test_18d.txt", "Expected\n136 steps: a f b j g n h d l o e p c i k m\n");
	solve("input\\test_18e.txt", "Expected\n81 steps: a c f i d g b e h\n");
	solve("input\\day_18.txt", "Expected\n3216 steps\n");
}

void day_18::solve(const std::string& input, const std::string& expected_result) {
	std::cout << "\nSolving: " << input << '\n';
	std::vector<std::vector<char>> grid = helper::file_to_grid(input);

	//helper::print_grid(grid);

	std::set<char> exceptions({ '#' });

	UnweightedGraph graph = helper::grid_to_graph(grid, exceptions);
	Position start = helper::find_position(graph, '@');
	//helper::print_graph(graph);
	std::set<char> keys = find_keys(graph);
	//print_graph_info(graph);

	//std::cout << "Removing dead ends\n";
	graph = remove_dead_ends(graph);
	//print_graph_info(graph);
	//std::cout << "Convert to unweighted graph:\n";
	WeightedGraph w_graph = make_weighted(graph);
	//print_graph_info(w_graph);
	//std::cout << "Remove bridges:\n";
	remove_bridges(w_graph);
	//print_graph_info(w_graph);
	print_graph(w_graph);

	//print_keys(keys);
	std::cout << expected_result;
	//std::cout << "BFS on unweighted graph;\n";
	//path_result result = bredth_first_search(graph, start, keys);
	//std::cout << result.steps << " steps:";
	//for (const auto& [k, v] : result.path) {
	//	if (islower(v.id)) {
	//		std::cout << ' ' << v.id;
	//	}
	//}
	//std::cout << "\nVertices visited : " << result.vertex_visited << '\n';

	//std::cout << "BFS with a priority queue on weighted graph;\n";
	path_result result = bredth_first_search(w_graph, start, keys);
	std::cout << result.steps << " steps:";
	for (const auto& [k, v] : result.path) {
		if (islower(v.id)) {
			std::cout << ' ' << v.id;
		}
	}
	std::cout << "\nVertices visited : " << result.vertex_visited << '\n';
}


std::set<char> day_18::find_keys(const UnweightedGraph& graph) {
	std::set<char> keys;
	for (const auto& [node, neighbours] : graph) {
		if (islower(node.id)) {
			keys.insert(node.id);
		}
	}
	return keys;
}

path_result day_18::bredth_first_search(const UnweightedGraph& graph, const Position& start, const std::set<char> keys) {

	path_result result;

	std::queue < std::pair<Position, std::set<char>>> q;
	std::set<char> e;
	std::pair<Position, std::set<char>> s = std::make_pair(start, e);
	q.push(s);

	std::map< std::pair<Position, std::set<char>>, std::pair<Position, std::set<char>>> visited;
	visited[s] = s;

	while (!q.empty()) {
		std::pair<Position, std::set<char>> prev = q.front();
		auto [pos, k] = prev;
		q.pop();
		++result.vertex_visited;
		//std::cout << "Visiting: " << pos << '\n';
		//print_keys(k);
		// exit once all the keys are collected
		if (k == keys) {
			//std::cout << "FOUND ALL THE KEYS!\n";
			while (prev != s) {
				++result.steps;
				std::pair<Position, std::set<char>> current = prev;
				prev = visited[prev];
				result.path[prev.first] = current.first;
				//std::cout << current.first << "->";
			}
			//std::cout << start << '\n';
			return result;
		}
		// iterate through the neighbours
		for (const Position& p : graph.at(pos)) {
			//std::cout << "Neighbour at: " << p << '\n';
			std::set<char> k_updated(k);
			// collect key
			if (islower(p.id)) {
				//std::cout << "Found key!\n";
				k_updated.insert(p.id);
			}
			// if the neighbour is a door (capital letter), add it to the list only if you have the key
			if (isupper(p.id)) {
				//std::cout << "Door: " << p.id << '\n';
				//print_keys(k);
				char c = static_cast<char>(tolower(p.id));
				if (k.find(c) == k.end()) {
					//std::cout << "cant open door\n";
					continue;
				}
			}
			// add the position and the set of keys to the list of visited nodes if not already visited
			std::pair<Position, std::set<char>> new_state = std::make_pair(p, k_updated);
			if (visited.find(new_state) == visited.end()) {
				//std::cout << "Queued new neighbour\n";
				visited[new_state] = prev;
				q.push(new_state);
			}
		}
	}

	return result;
}

path_result bredth_first_search(const WeightedGraph& graph, const Position& start, const std::set<char> keys) {
	path_result result;

	using Next = std::pair < Position, std::pair<int, std::set<char>>>;

	auto comp = [](const Next a, const Next b) -> bool {
		if (a.second.first > b.second.first) {
			return true;
		}
		return a.second.first == b.second.first && a.second.second.size() < b.second.second.size();
	};
	
	std::priority_queue < Next, std::vector<Next>, decltype(comp)> q(comp);
	std::set<char> e;
	Next s = std::make_pair(start, std::make_pair(0, e));
	q.push(s);
	std::map< std::pair<Position, std::set<char>>, std::pair<Position, std::set<char>>> visited;
	visited[std::make_pair(start, e)] = std::make_pair(start, e);

	while (!q.empty()) {
		Next prev = q.top();
		auto& [pos, info] = prev;
		auto& [current_steps, k] = info;
		q.pop();
		++result.vertex_visited;

		if (k == keys) {
			result.steps = current_steps;
			return result;
		}

		for (const auto& p : graph.at(pos)) {
			std::set<char> k_updated(k);
			if (islower(p.first.id)) {
				//std::cout << "Found key!\n";
				k_updated.insert(p.first.id);
			}

			if (isupper(p.first.id)) {
				//std::cout << "Door: " << p.id << '\n';
				//print_keys(k);
				char c = static_cast<char>(tolower(p.first.id));
				if (k.find(c) == k.end()) {
					//std::cout << "cant open door\n";
					continue;
				}
			}
			// add the position and the set of keys to the list of visited nodes if not already visited
			int steps = current_steps + p.second;
			Next new_state = std::make_pair(p.first, std::make_pair(steps, k_updated));
			std::pair<Position, std::set<char>> pos_k = std::make_pair(p.first, k_updated);
			if (visited.find(pos_k) == visited.end()) {
				visited[pos_k] = std::make_pair(pos, k);
				q.push(new_state);
			}
		}
	}

	return result;
}