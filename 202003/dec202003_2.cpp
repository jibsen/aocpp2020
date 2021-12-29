//
// Advent of Code 2020, day 3, part two
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

long trees_encountered(const Map &map, int dx, int dy)
{
	long num_trees = 0;

	for (int x = 0, y = 0; y < map.size(); ) {
		num_trees += static_cast<long>(map[y][x] == '#');

		x = (x + dx) % map[y].size();
		y += dy;
	}

	return num_trees;
}

int main()
{
	const auto map = read_map();

	std::cout << trees_encountered(map, 1, 1) * trees_encountered(map, 3, 1)
	           * trees_encountered(map, 5, 1) * trees_encountered(map, 7, 1)
		   * trees_encountered(map, 1, 2) << '\n';
}
