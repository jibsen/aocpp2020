//
// Advent of Code 2020, day 11, part two
//

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <ranges>
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

std::size_t num_neighbors(const Map &map, int start_x, int start_y)
{
	constexpr std::array<std::pair<int, int>, 8> directions = {{
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, -1}, {1, 0}, {1, 1}
	}};

	auto inside_map = [&map](int x, int y) {
		return y >= 0 && y < map.size()
		    && x >= 0 && x < map[y].size();
	};

	return std::ranges::count_if(directions,
		[&](auto dir) {
			auto [dx, dy] = dir;

			for (int x = start_x, y = start_y; inside_map(x + dx, y + dy); x += dx, y += dy) {
				switch (map[y + dy][x + dx]) {
				case '#':
					return true;
				case 'L':
					return false;
				}
			}

			return false;
		}
	);
}

bool update_map(Map &map)
{
	Map new_map(map);

	bool change = false;

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].size(); ++x) {
			switch (map[y][x]) {
			case 'L':
				if (num_neighbors(map, x, y) == 0) {
					new_map[y][x] = '#';
					change = true;
				}
				break;
			case '#':
				if (num_neighbors(map, x, y) >= 5) {
					new_map[y][x] = 'L';
					change = true;
				}
				break;
			}
		}
	}

	map.swap(new_map);

	return change;
}

int main()
{
	auto map = read_map();

	for (;;) {
		if (!update_map(map)) {
			break;
		}
	}

	std::cout << std::ranges::count(map | std::views::join, '#') << '\n';
}
