//
// Advent of Code 2020, day 14, part two
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
	std::uint64_t mask = 0;
	std::uint64_t floating = 0;
	std::uint64_t bit = std::uint64_t(1) << 35;

	for (auto ch : sv) {
		switch (ch) {
		case '1':
			mask |= bit;
			break;
		case 'X':
			floating |= bit;
			break;
		}

		bit >>= 1;
	}

	return {mask, floating};
}

std::vector<std::uint64_t> get_floating_addresses(std::uint64_t floating)
{
	std::vector<std::uint64_t> addresses = { 0 };

	std::uint64_t bit = std::uint64_t(1) << 35;

	for (; bit != 0; bit >>= 1) {
		if (floating & bit) {
			std::vector<std::uint64_t> new_addresses;

			for (auto addr : addresses) {
				new_addresses.push_back(addr | bit);
			}

			addresses.insert(addresses.end(), new_addresses.begin(), new_addresses.end());
		}
	}

	return addresses;
}

int main()
{
	std::unordered_map<std::uint64_t, std::uint64_t> memory;

	std::uint64_t mask = 0;
	std::uint64_t floating = 0;
	std::vector<std::uint64_t> addresses = { 0 };

	for (std::string line; std::getline(std::cin, line); ) {
		if (line.starts_with("mask")) {
			std::tie(mask, floating) = read_mask(line.substr(7));
			addresses = get_floating_addresses(floating);
			continue;
		}

		std::uint64_t address = std::stoi(line.substr(4));
		std::uint64_t value = std::stoi(line.substr(line.find('=') + 1));

		for (auto addr : addresses) {
			memory[((address | mask) & ~floating) | addr] = value;
		}
	}

	auto value_view = memory | std::views::values | std::views::common;

	std::cout << std::accumulate(value_view.begin(), value_view.end(), std::uint64_t(0)) << '\n';
}
