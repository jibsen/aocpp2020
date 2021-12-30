//
// Advent of Code 2020, day 4, part one
//

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

auto split_ws(std::string_view sv)
{
	const auto is_ws = [](unsigned char ch) { return std::isspace(ch); };

	std::vector<std::string_view> res;

	auto pos = sv.begin();

	for (;;) {
		pos = std::find_if_not(pos, sv.end(), is_ws);

		if (pos == sv.end()) {
			break;
		}

		auto start = pos;

		pos = std::find_if(pos, sv.end(), is_ws);

		res.push_back(sv.substr(start - sv.begin(), pos - start));
	}

	return res;
}

auto read_passports()
{
	std::vector<std::string> passports;
	std::string passport;

	for (std::string line; std::getline(std::cin, line); ) {
		if (line.empty()) {
			passports.push_back(std::move(passport));
			passport = "";
			continue;
		}

		passport.append(" ");
		passport.append(line);
	}

	if (!passport.empty()) {
		passports.push_back(std::move(passport));
	}

	return passports;
}

std::uint8_t key_flag(std::string_view key)
{
	static const std::unordered_map<std::string_view, std::uint8_t> lookup = {
		{ "byr", 1U << 7 }, { "iyr", 1U << 6 }, { "eyr", 1U << 5 },
		{ "hgt", 1U << 4 }, { "hcl", 1U << 3 }, { "ecl", 1U << 2 },
		{ "pid", 1U << 1 }, { "cid", 1U }
	};

	return lookup.at(key);
}

bool is_valid(std::string_view passport)
{
	constexpr std::uint8_t required_fields_mask = 0xFE;

	auto entries = split_ws(passport);

	std::uint8_t fields = 0;

	for (auto entry : entries) {
		fields |= key_flag(entry.substr(0, 3));
	}

	return (fields & required_fields_mask) == required_fields_mask;
}

int main()
{
	const auto passports = read_passports();

	std::cout << std::format("{} passports read\n", passports.size());

	std::cout << std::ranges::count_if(passports, is_valid) << '\n';
}
