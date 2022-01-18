//
// Advent of Code 2020, day 23, part two
//

// Surely there is a more efficient solution, but simply simulating the
// full game like this takes about an hour.

#include <algorithm>
#include <array>
#include <deque>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>

int main()
{
	const std::deque<long> initial_cups = {2, 1, 9, 7, 4, 8, 3, 6, 5};

	constexpr long num_cups = 1'000'000;
	constexpr std::size_t num_rounds = 10'000'000;

	std::deque<long> cups(num_cups);

	std::iota(cups.begin(), cups.end(), 1);

	std::ranges::copy(initial_cups, cups.begin());

	for (std::size_t round = 1; round <= num_rounds; ++round) {
		const std::array<long, 3> picked = { cups[1], cups[2], cups[3] };

		long target = cups[0] - 1;

		if (target == 0) {
			target = num_cups;
		}

		while (std::ranges::find(picked, target) != picked.end()) {
			--target;

			if (target == 0) {
				target = num_cups;
			}
		}

		// The erase and insert are equivalent to a rotate, but on
		// a deque this is often faster since operations near either
		// end are cheap

		cups.erase(cups.begin() + 1, cups.begin() + 4);

		cups.insert(std::ranges::find(cups, target) + 1, picked.begin(), picked.end());

		// Rotate cups so the new current is in front
		auto current = cups.front();
		cups.pop_front();
		cups.push_back(current);
	}

	std::ranges::rotate(cups, std::ranges::find(cups, 1));

	std::cout << cups[1] * cups[2] << '\n';
}
