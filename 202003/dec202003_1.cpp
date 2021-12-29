//
// Advent of Code 2020, day 3, part one
//

#include <iostream>
#include <string>
#include <vector>

using Map = std::vector<std::string>;

auto read_map()
{
	Map map;

	for (std::string line; std::cin >> line; ) {
		map.push_back(std::move(line));
	}

	return map;
}

int main()
{
	const auto map = read_map();

	int num_trees = 0;

	for (int x = 0, y = 0; y < map.size(); ) {
		num_trees += static_cast<int>(map[y][x] == '#');

		x = (x + 3) % map[y].size();
		y += 1;
	}

	std::cout << num_trees << '\n';
}
