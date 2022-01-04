//
// Advent of Code 2020, day 17, part one
//

#include <array>
#include <format>
#include <iostream>
#include <string>
#include <unordered_set>

struct ArrayHash {
	template<typename T, std::size_t size>
	std::size_t operator()(const std::array<T, size> &array) const noexcept
	{
		std::size_t hash = 17;
		for (const auto &elem : array) {
			hash = hash * 37 + std::hash<T>()(elem);
		}
		return hash;
	}
};

using Vec3 = std::array<int, 3>;

using State = std::unordered_set<Vec3, ArrayHash>;

auto read_initial_state()
{
	State state;

	int y = 0;

	for (std::string line; std::getline(std::cin, line); ++y) {
		for (int x = 0; x != line.size(); ++x) {
			if (line[x] == '#') {
				state.insert({x, y, 0});
			}
		}
	}

	return state;
}

static constexpr auto deltas = [] {
	std::array<Vec3, 27> res = {};

	std::size_t idx = 0;

	for (int dx : { -1, 0, 1 }) {
		for (int dy : { -1, 0, 1 }) {
			for (int dz : { -1, 0, 1 }) {
				res[idx++] = {dx, dy, dz};
			}
		}
	}

	return res;
}();

int active_neighbors(const State &state, int x, int y, int z)
{
	int num = 0;

	for (auto [dx, dy, dz] : deltas) {
		if (dx == 0 && dy == 0 && dz == 0) {
			continue;
		}

		num += static_cast<int>(state.contains({x + dx, y + dy, z + dz}));
	}

	return num;
}

void advance_state(State &state)
{
	State to_check;

	for (auto [x, y, z] : state) {
		for (auto [dx, dy, dz] : deltas) {
			to_check.insert({x + dx, y + dy, z + dz});
		}
	}

	State next_state;

	for (auto [x, y, z] : to_check) {
		int neighbors = active_neighbors(state, x, y, z);

		if (state.contains({x, y, z})) {
			if (neighbors == 2 || neighbors == 3) {
				next_state.insert({x, y, z});
			}
		}
		else {
			if (neighbors == 3) {
				next_state.insert({x, y, z});
			}
		}
	}

	state.swap(next_state);
}

int main()
{
	auto state = read_initial_state();

	std::cout << std::format("{} active cubes read\n", state.size());

	for (int step = 0; step < 6; ++step) {
		advance_state(state);
	}

	std::cout << state.size() << '\n';
}
