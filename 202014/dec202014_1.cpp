//
// Advent of Code 2020, day 14, part one
//

#include <cstdint>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>

std::pair<std::uint64_t, std::uint64_t> read_mask(std::string_view sv)
{
	std::uint64_t mask = -1;
	std::uint64_t replace = 0;
	std::uint64_t bit = std::uint64_t(1) << 35;

	for (auto ch : sv) {
		switch (ch) {
		case '1':
			replace |= bit;
			[[fallthrough]];
		case '0':
			mask ^= bit;
			break;
		}

		bit >>= 1;
	}

	return {mask, replace};
}

int main()
{
	std::unordered_map<std::uint64_t, std::uint64_t> memory;

	std::uint64_t mask = -1;
	std::uint64_t replace = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		if (line.starts_with("mask")) {
			std::tie(mask, replace) = read_mask(line.substr(7));
			continue;
		}

		std::uint64_t address = std::stoi(line.substr(4));
		std::uint64_t value = std::stoi(line.substr(line.find('=') + 1));

		memory[address] = (value & mask) | replace;
	}

	auto value_view = memory | std::views::values | std::views::common;

	std::cout << std::accumulate(value_view.begin(), value_view.end(), std::uint64_t(0)) << '\n';
}
