//
// Advent of Code 2020, day 12, part one
//

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

auto read_instructions()
{
	std::vector<std::pair<char, int>> instructions;

	char action = '\0';
	int value = -1;

	while (std::cin >> action >> value) {
		instructions.push_back({action, value});
	}

	return instructions;
}

int main()
{
	static const std::unordered_map<int, std::pair<int, int>> delta = {
		{0, {1, 0}}, {90, {0, 1}}, {180, {-1, 0}}, {270, {0, -1}}
	};

	auto instructions = read_instructions();

	int facing = 0;
	long long x = 0;
	long long y = 0;

	for (auto [action, value] : instructions) {
		switch (action) {
		case 'N':
			y += value;
			break;
		case 'S':
			y -= value;
			break;
		case 'E':
			x += value;
			break;
		case 'W':
			x -= value;
			break;
		case 'L':
			facing = (facing + value) % 360;
			break;
		case 'R':
			facing -= value;
			if (facing < 0) {
				facing += 360;
			}
			break;
		case 'F':
			auto [dx, dy] = delta.at(facing);
			x += dx * value;
			y += dy * value;
			break;
		}
	}

	std::cout << std::abs(x) + std::abs(y) << '\n';
}
