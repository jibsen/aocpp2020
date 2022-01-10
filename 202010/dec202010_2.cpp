//
// Advent of Code 2020, day 10, part two
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main()
{
	std::vector<int> ratings(
		std::istream_iterator<int>{std::cin},
		std::istream_iterator<int>{}
	);

	std::ranges::sort(ratings);

	std::vector<std::size_t> num_arrangements(ratings.back() + 4, 0);

	num_arrangements[ratings.back() + 1] = 0;
	num_arrangements[ratings.back() + 2] = 0;
	num_arrangements[ratings.back() + 3] = 1;

	for (auto rating : ratings | std::views::reverse) {
		num_arrangements[rating] = num_arrangements[rating + 1]
		                         + num_arrangements[rating + 2]
		                         + num_arrangements[rating + 3];

	}

	num_arrangements[0] = num_arrangements[1] + num_arrangements[2] + num_arrangements[3];

	std::cout << num_arrangements[0] << '\n';
}
