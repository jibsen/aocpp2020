//
// Advent of Code 2020, day 20, part one
//

#include <algorithm>
#include <format>
#include <iostream>
#include <queue>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <vector>

struct PairHash {
	template<typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2> &p) const noexcept
	{
		std::size_t h1 = std::hash<T1>()(p.first);
		std::size_t h2 = std::hash<T2>()(p.second);
		return (17 * 37 + h1) * 37 + h2;
	}
};

struct Tile {
	int id = 0;
	std::vector<std::string> data;
};

auto read_tiles()
{
	std::unordered_map<int, Tile> tiles;
	Tile tile;

	for (std::string line; std::getline(std::cin, line); ) {
		if (line.empty()) {
			continue;
		}

		if (line.starts_with("Tile")) {
			if (!tile.data.empty()) {
				tiles.emplace(tile.id, std::move(tile));
				tile.data.clear();
			}

			tile.id = std::stoi(line.substr(5));

			continue;
		}

		tile.data.push_back(std::move(line));
	}

	if (!tile.data.empty()) {
		tiles.emplace(tile.id, std::move(tile));
	}

	return tiles;
}

void flip_vertical(std::span<std::string> sp)
{
	std::ranges::reverse(sp);
}

void flip_horizontal(std::span<std::string> sp)
{
	std::ranges::for_each(sp, [](auto &row) { std::ranges::reverse(row); });
}

void transpose(std::span<std::string> sp)
{
	for (int i = 0; i < sp.size(); ++i) {
		for (int j = i + 1; j < sp.size(); ++j) {
			std::swap(sp[i][j], sp[j][i]);
		}
	}
}

void rotate(std::span<std::string> sp)
{
	transpose(sp);
	flip_vertical(sp);
}

std::string get_top(const Tile &tile)
{
	return tile.data.front();
}

std::string get_bottom(const Tile &tile)
{
	return tile.data.back();
}

std::string get_left(const Tile &tile)
{
	std::string left;

	left.reserve(tile.data.size());

	for (const auto &row : tile.data) {
		left.push_back(row.front());
	}

	return left;
}

std::string get_right(const Tile &tile)
{
	std::string right;

	right.reserve(tile.data.size());

	for (const auto &row : tile.data) {
		right.push_back(row.back());
	}

	return right;
}

void rotate_to_match(Tile &tile, std::string_view target, auto get_edge)
{
	for (auto op : "vhvrvhv") {
		if (get_edge(tile) == target) {
			return;
		}

		switch (op) {
		case 'v':
			flip_vertical(tile.data);
			break;
		case 'h':
			flip_horizontal(tile.data);
			break;
		case 'r':
			rotate(tile.data);
			break;
		}

	}
}

int main()
{
	auto tiles = read_tiles();

	std::cout << std::format("{} tiles read\n", tiles.size());

	std::unordered_map<std::string, std::vector<int>> tiles_with_edge;

	int start_id = 0;

	for (const auto &tile : tiles | std::views::values) {
		start_id = tile.id;

		auto top = get_top(tile);
		auto bottom = get_bottom(tile);
		auto left = get_left(tile);
		auto right = get_right(tile);

		tiles_with_edge[top].push_back(tile.id);
		tiles_with_edge[bottom].push_back(tile.id);
		tiles_with_edge[left].push_back(tile.id);
		tiles_with_edge[right].push_back(tile.id);

		std::ranges::reverse(top);
		std::ranges::reverse(bottom);
		std::ranges::reverse(left);
		std::ranges::reverse(right);

		tiles_with_edge[top].push_back(tile.id);
		tiles_with_edge[bottom].push_back(tile.id);
		tiles_with_edge[left].push_back(tile.id);
		tiles_with_edge[right].push_back(tile.id);
	}

	// Check no edge belongs to more than two tiles
	for (const auto &[k, v] : tiles_with_edge) {
		if (v.size() > 2) {
			std::cerr << std::format("'{}' occurs {} times\n", k, v.size());
			exit(1);
		}
	}

	// We picked a start_id above, now place that tile at 0, 0 and
	// find the relative position of the rest of the tiles by
	// matching the edges to find neighbors

	std::unordered_map<std::pair<int, int>, int, PairHash> map;
	std::queue<std::tuple<int, int, int>> queue;

	queue.push({start_id, 0, 0});
	map.insert({{0, 0}, start_id});

	while (!queue.empty()) {
		auto [cur, x, y] = queue.front();
		queue.pop();

		auto top = get_top(tiles[cur]);

		std::erase(tiles_with_edge[top], cur);

		if (!tiles_with_edge[top].empty()) {
			int id = tiles_with_edge[top].front();

			if (auto [it, success] = map.insert({{x, y + 1}, id}); success) {
				rotate_to_match(tiles[id], top, get_bottom);

				queue.push({id, x, y + 1});
			}
		}

		auto bottom = get_bottom(tiles[cur]);

		std::erase(tiles_with_edge[bottom], cur);

		if (!tiles_with_edge[bottom].empty()) {
			int id = tiles_with_edge[bottom].front();

			if (auto [it, success] = map.insert({{x, y - 1}, id}); success) {
				rotate_to_match(tiles[id], bottom, get_top);

				queue.push({id, x, y - 1});
			}
		}

		auto left = get_left(tiles[cur]);

		std::erase(tiles_with_edge[left], cur);

		if (!tiles_with_edge[left].empty()) {
			int id = tiles_with_edge[left].front();

			if (auto [it, success] = map.insert({{x - 1, y}, id}); success) {
				rotate_to_match(tiles[id], left, get_right);

				queue.push({id, x - 1, y});
			}
		}

		auto right = get_right(tiles[cur]);

		std::erase(tiles_with_edge[right], cur);

		if (!tiles_with_edge[right].empty()) {
			int id = tiles_with_edge[right].front();

			if (auto [it, success] = map.insert({{x + 1, y}, id}); success) {
				rotate_to_match(tiles[id], right, get_left);

				queue.push({id, x + 1, y});
			}
		}
	}

	// Find the range of coordinates of the tiles
	int x_min = std::numeric_limits<int>::max();
	int y_min = std::numeric_limits<int>::max();
	int x_max = std::numeric_limits<int>::min();
	int y_max = std::numeric_limits<int>::min();

	for (auto [x, y] : map | std::views::keys) {
		x_min = std::min(x_min, x);
		y_min = std::min(y_min, y);
		x_max = std::max(x_max, x);
		y_max = std::max(y_max, y);
	}

	std::cout << static_cast<long long>(map[{x_min, y_min}])
	           * static_cast<long long>(map[{x_min, y_max}])
	           * static_cast<long long>(map[{x_max, y_min}])
	           * static_cast<long long>(map[{x_max, y_max}]) << '\n';
}
