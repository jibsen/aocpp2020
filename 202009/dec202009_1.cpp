//
// Advent of Code 2020, day 9, part one
//

#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

int main()
{
	std::vector<long long> data(std::istream_iterator<long long>{std::cin},
	                            std::istream_iterator<long long>{});

	std::unordered_set<long long> seen;

	constexpr int preamble_length = 25;

	for (int i = 0; i < preamble_length; ++i) {
		seen.insert(data[i]);
	}

	for (int i = preamble_length; i < data.size(); ++i) {
		bool found = false;

		for (int j = preamble_length; j > 0; --j) {
			if (data[i] != 2 * data[i - j]
			 && seen.contains(data[i] - data[i - j])) {
				found = true;
				break;
			}
		}

		if (!found) {
			std::cout << data[i] << '\n';
			break;
		}

		seen.erase(data[i - preamble_length]);
		seen.insert(data[i]);
	}
}
