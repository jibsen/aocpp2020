//
// Advent of Code 2020, day 23, part one
//

#include <algorithm>
#include <array>
#include <deque>
#include <format>
#include <iostream>
#include <iterator>
#include <ranges>

int main()
{
	std::deque<int> cups = {2, 1, 9, 7, 4, 8, 3, 6, 5};

	for (int round = 1; round <= 100; ++round) {
		const std::array<int, 3> picked = { cups[1], cups[2], cups[3] };

		int target = cups[0] - 1;

		if (target == 0) {
			target = 9;
		}

		while (std::ranges::find(picked, target) != picked.end()) {
			--target;

			if (target == 0) {
				target = 9;
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

	std::ranges::copy(cups | std::views::drop(1), std::ostream_iterator<int>(std::cout));
	std::cout << '\n';
}
