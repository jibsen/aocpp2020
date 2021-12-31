//
// Advent of Code 2020, day 5, part one
//

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

constexpr unsigned int seat_to_id(std::string_view seat)
{
	unsigned int id = 0;
	unsigned int mask = 1;

	for (auto ch : seat | std::views::reverse) {
		if (ch == 'B' || ch == 'R') {
			id |= mask;
		}
		mask <<= 1;
	}

	return id;
}

int main()
{
	unsigned int max_value = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		max_value = std::max(max_value, seat_to_id(line));
	}

	std::cout << max_value << '\n';
}
