//
// Advent of Code 2020, day 1, part one
//

#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

int main()
{
	std::vector<long> report(std::istream_iterator<long>{std::cin},
	                         std::istream_iterator<long>{});

	std::unordered_set<long> seen;

	for (auto cur : report) {
		if (seen.contains(2020 - cur)) {
			std::cout << cur * (2020 - cur) << '\n';
			break;
		}

		seen.insert(cur);
	}
}
