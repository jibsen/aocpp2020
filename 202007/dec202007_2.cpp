//
// Advent of Code 2020, day 7, part two
//

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string>>>;

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

			adj[from].emplace_back(num, std::move(to));

			ss >> token;

			if (token.ends_with('.')) {
				break;
			}
		}
	}

	return adj;
}

std::size_t num_contained_bags(const Graph &adj, const std::string &bag)
{
	if (!adj.contains(bag)) {
		return 1;
	}

	std::size_t num_contained = 0;

	for (const auto &[num, next] : adj.at(bag)) {
		num_contained += num * num_contained_bags(adj, next);
	}

	return 1 + num_contained;
}

int main()
{
	auto adj = read_rules();

	std::cout << num_contained_bags(adj, "shinygold") - 1 << '\n';
}
