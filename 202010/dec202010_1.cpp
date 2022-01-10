//
// Advent of Code 2020, day 10, part one
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
	std::vector<int> ratings(
		std::istream_iterator<int>{std::cin},
		std::istream_iterator<int>{}
	);

	std::ranges::sort(ratings);

	std::vector<int> deltas;

	std::adjacent_difference(ratings.begin(), ratings.end(), std::back_inserter(deltas));

	std::cout << std::ranges::count(deltas, 1) * (std::ranges::count(deltas, 3) + 1) << '\n';
}
