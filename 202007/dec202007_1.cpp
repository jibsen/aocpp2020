//
// Advent of Code 2020, day 7, part one
//

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

auto read_rules()
{
	Graph adj;

	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream ss(line);

		std::string token;
		std::string from;

		ss >> from >> token;
		from += token;

		ss >> token >> token;

		for (;;) {
			std::string to;
			int num = 0;

			ss >> token;

			if (token == "no") {
				break;
			}

			num = std::stoi(token);

			ss >> to >> token;
			to += token;

			adj[to].push_back(from);

			ss >> token;

			if (token.ends_with('.')) {
				break;
			}
		}
	}

	return adj;
}

std::size_t count_containing_bags(const Graph &adj, const std::string &start)
{
	std::unordered_set<std::string> visited;
	std::queue<std::string> queue;

	queue.push(start);

	std::size_t num_containing = 0;

	while (!queue.empty()) {
		auto cur = queue.front();
		queue.pop();

		if (auto [it, success] = visited.insert(cur); !success) {
			continue;
		}

		++num_containing;

		if (auto it = adj.find(cur); it != adj.end()) {
			for (const auto &next : it->second) {
				queue.push(next);
			}
		}
	}

	return num_containing - 1;
}

int main()
{
	auto adj = read_rules();

	std::cout << count_containing_bags(adj, "shinygold") << '\n';
}
