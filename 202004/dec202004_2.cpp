//
// Advent of Code 2020, day 4, part two
//

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <format>
#include <functional>
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

constexpr auto is_digit = [](char ch) { return ch >= '0' && ch <= '9'; };
constexpr auto is_hex = [](char ch) {
	return (ch >= '0' && ch <= '9')
	    || (ch >= 'a' && ch <= 'f');
};

bool is_byr_valid(std::string_view value)
{
	if (value.size() != 4 || !std::ranges::all_of(value, is_digit)) {
		return false;
	}

	int year = std::stoi(std::string(value));

	return year >= 1920 && year <= 2002;
}

bool is_iyr_valid(std::string_view value)
{
	if (value.size() != 4 || !std::ranges::all_of(value, is_digit)) {
		return false;
	}

	int year = std::stoi(std::string(value));

	return year >= 2010 && year <= 2020;
}

bool is_eyr_valid(std::string_view value)
{
	if (value.size() != 4 || !std::ranges::all_of(value, is_digit)) {
		return false;
	}

	int year = std::stoi(std::string(value));

	return year >= 2020 && year <= 2030;
}

bool is_hgt_valid(std::string_view value)
{
	if (value.size() < 3) {
		return false;
	}

	auto suffix = value.substr(value.size() - 2);
	value.remove_suffix(2);

	if (!std::ranges::all_of(value, is_digit)) {
		return false;
	}

	if (suffix == "cm") {
		int height = std::stoi(std::string(value));

		return height >= 150 && height <= 193;
	}
	else if (suffix == "in") {
		int height = std::stoi(std::string(value));

		return height >= 59 && height <= 76;
	}

	return false;
}

bool is_hcl_valid(std::string_view value)
{
	return value.size() == 7
	    && value.starts_with('#')
	    && std::ranges::all_of(value.substr(1), is_hex);
}

bool is_ecl_valid(std::string_view value)
{
	static const std::array<std::string_view, 7> valid_colors = {
		"amb", "blu", "brn", "gry", "grn", "hzl", "oth"
	};

	return std::ranges::find(valid_colors, value) != valid_colors.end();
}

bool is_pid_valid(std::string_view value)
{
	return value.size() == 9 && std::ranges::all_of(value, is_digit);
}

bool is_cid_valid(std::string_view value)
{
	return true;
}

bool is_entry_valid(std::string_view entry)
{
	static const std::unordered_map<std::string_view, std::function<bool(std::string_view)>> lookup = {
		{ "byr", is_byr_valid }, { "iyr", is_iyr_valid }, { "eyr", is_eyr_valid },
		{ "hgt", is_hgt_valid }, { "hcl", is_hcl_valid }, { "ecl", is_ecl_valid },
		{ "pid", is_pid_valid }, { "cid", is_cid_valid }
	};

	return lookup.at(entry.substr(0, 3))(entry.substr(4));
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

		if (!is_entry_valid(entry)) {
			return false;
		}
	}

	return (fields & required_fields_mask) == required_fields_mask;
}

int main()
{
	const auto passports = read_passports();

	std::cout << std::format("{} passports read\n", passports.size());

	std::cout << std::ranges::count_if(passports, is_valid) << '\n';
}
