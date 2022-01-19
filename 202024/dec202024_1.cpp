//
// Advent of Code 2020, day 24, part one
//

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

	std::cout << black_tiles.size() << '\n';
}
