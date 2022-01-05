//
// Advent of Code 2020, day 9, part two
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
	std::vector<long long> data(std::istream_iterator<long long>{std::cin},
	                            std::istream_iterator<long long>{});

	constexpr long long target_sum = 1124361034LL;

	auto left = data.cbegin();
	auto right = data.cbegin();
	long long sum = 0;

	for (;;) {
		if (sum < target_sum) {
			sum += *right++;
		}
		else if (sum > target_sum) {
			sum -= *left++;
		}
		else {
			auto [min, max] = std::ranges::minmax_element(left, right);
			std::cout << *min + *max << '\n';
			break;
		}
	}
}
