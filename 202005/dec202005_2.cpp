//
// Advent of Code 2020, day 5, part two
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

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
	std::vector<unsigned int> seat_ids;

	std::transform(
		std::istream_iterator<std::string>{std::cin},
		std::istream_iterator<std::string>{},
		std::back_inserter(seat_ids),
		seat_to_id
	);

	std::ranges::sort(seat_ids);

	constexpr auto not_consecutive = [](auto lhs, auto rhs) { return rhs != lhs + 1; };

	if (auto it = std::ranges::adjacent_find(seat_ids, not_consecutive); it != seat_ids.end()) {
		std::cout << *it + 1 << '\n';
	}
}
