//
// Advent of Code 2020, day 1, part two
//

#include <iostream>
#include <iterator>
#include <optional>
#include <span>
#include <unordered_set>
#include <vector>

std::optional<long> prod_of_target_sum(std::span<const long> span, long target)
{
	std::unordered_set<long> seen;

	for (auto cur : span) {
		if (seen.contains(target - cur)) {
			return cur * (target - cur);
		}

		seen.insert(cur);
	}

	return {};
}

int main()
{
	std::vector<long> report(std::istream_iterator<long>{std::cin},
	                         std::istream_iterator<long>{});

	for (auto it = report.begin(); it != report.end(); ++it) {
		if (auto prod = prod_of_target_sum(std::span(std::next(it), report.end()), 2020 - *it)) {
			std::cout << *prod * *it << '\n';
		}
	}
}
