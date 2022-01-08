//
// Advent of Code 2020, day 15, part one
//

#include <iostream>
#include <unordered_map>
#include <vector>

auto read_starting_numbers()
{
	std::vector<long long> numbers;

	long long num = 0;

	for (char sep = ','; sep == ',' && std::cin >> num; std::cin >> sep) {
		numbers.push_back(num);
	}

	return numbers;
}

int main()
{
	auto numbers = read_starting_numbers();

	std::unordered_map<long long, long long> last_seen;

	for (int turn = 1; turn < numbers.size(); ++turn) {
		last_seen.insert({numbers[turn - 1], turn});
	}

	long long next = numbers.back();

	for (long long turn = numbers.size(); turn < 2020; ++turn) {
		if (auto [it, success] = last_seen.insert({next, turn}); success) {
			next = 0;
		}
		else {
			next = turn - it->second;
			it->second = turn;
		}
	}

	std::cout << next << '\n';
}
