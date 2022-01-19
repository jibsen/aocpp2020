//
// Advent of Code 2020, day 24, part two
//

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

struct PairHash {
	template<typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2> &p) const noexcept
	{
		std::size_t h1 = std::hash<T1>()(p.first);
		std::size_t h2 = std::hash<T2>()(p.second);
		return (17 * 37 + h1) * 37 + h2;
	}
};

std::size_t num_neighbors(const std::unordered_set<std::pair<int, int>, PairHash> &black_tiles, int x, int y)
{
	static constexpr std::array<std::pair<int, int>, 6> directions = {{
		{2, 0}, {1, -1}, {-1, -1}, {-2, 0}, {-1, 1}, {1, 1}
	}};

	return std::ranges::count_if(directions,
		[&](auto dir) {
			auto [dx, dy] = dir;
			return black_tiles.contains({x + dx, y + dy});
		}
	);
}

int main()
{
	static const std::unordered_map<std::string_view, std::pair<int, int>> lookup = {
		{"e", {2, 0}}, {"se", {1, -1}}, {"sw", {-1, -1}},
		{"w", {-2, 0}}, {"nw", {-1, 1}}, {"ne", {1, 1}}
	};

	std::unordered_set<std::pair<int, int>, PairHash> black_tiles;

	for (std::string line; std::cin >> line; ) {
		int x = 0;
		int y = 0;

		for (std::string_view sv(line); !sv.empty(); ) {
			if (sv.starts_with('s') || sv.starts_with('n')) {
				auto [dx, dy] = lookup.at(sv.substr(0, 2));

				x += dx;
				y += dy;

				sv.remove_prefix(2);
			}
			else {
				auto [dx, dy] = lookup.at(sv.substr(0, 1));

				x += dx;
				y += dy;

				sv.remove_prefix(1);
			}
		}

		if (auto [it, success] = black_tiles.insert({x, y}); !success) {
			black_tiles.erase(it);
		}
	}

	for (int day = 1; day <= 100; ++day) {
		static constexpr std::array<std::pair<int, int>, 6> directions = {{
			{2, 0}, {1, -1}, {-1, -1}, {-2, 0}, {-1, 1}, {1, 1}
		}};

		auto to_check = black_tiles;

		for (auto [x, y] : black_tiles) {
			for (auto [dx, dy] : directions) {
				to_check.insert({x + dx, y + dy});
			}
		}

		auto next_black_tiles = black_tiles;

		for (auto [x, y] : to_check) {
			auto num = num_neighbors(black_tiles, x, y);

			if (black_tiles.contains({x, y})) {
				if (num == 0 || num > 2) {
					next_black_tiles.erase({x, y});
				}
			}
			else {
				if (num == 2) {
					next_black_tiles.insert({x, y});
				}
			}
		}

		black_tiles.swap(next_black_tiles);
	}

	std::cout << black_tiles.size() << '\n';
}
