//
// Advent of Code 2020, day 12, part two
//

#include <cstdlib>
#include <iostream>
#include <utility>
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
	auto instructions = read_instructions();

	long long ship_x = 0;
	long long ship_y = 0;
	long long wp_x = 10;
	long long wp_y = 1;

	for (auto [action, value] : instructions) {
		switch (action) {
		case 'N':
			wp_y += value;
			break;
		case 'S':
			wp_y -= value;
			break;
		case 'E':
			wp_x += value;
			break;
		case 'W':
			wp_x -= value;
			break;
		case 'L':
			for (; value >= 90; value -= 90) {
				wp_y = std::exchange(wp_x, -wp_y);
			}
			break;
		case 'R':
			for (; value >= 90; value -= 90) {
				wp_x = std::exchange(wp_y, -wp_x);
			}
			break;
		case 'F':
			ship_x += wp_x * value;
			ship_y += wp_y * value;
			break;
		}
	}

	std::cout << std::abs(ship_x) + std::abs(ship_y) << '\n';
}
