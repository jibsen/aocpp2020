//
// Advent of Code 2020, day 13, part two
//

// We use the computation using existence construction of the Chinese
// remainder theorem described at
// https://en.wikipedia.org/wiki/Chinese_remainder_theorem

#include <cstdint>
#include <format>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "wuint.hpp"

using wuint128 = wuint<4>;

template<std::size_t width>
std::ostream &operator<<(std::ostream &os, wuint<width> obj)
{
	constexpr uint32_t n = 1'000'000'000UL;

	if (obj.is_zero()) {
		os << '0';
		return os;
	}

	std::vector<std::uint32_t> parts;

	while (obj != 0) {
		parts.push_back(obj % n);
		obj /= n;
	}

	os << std::format("{}", parts.back());

	for (auto part : parts | std::views::reverse | std::views::drop(1)) {
		os << std::format("{:09}", part);
	}

	return os;
}

auto split(std::string_view sv, std::string_view delim)
{
	std::vector<std::string_view> res;

	std::string_view::size_type pos = 0;

	for (;;) {
		auto next_delim_pos = sv.find(delim, pos);

		res.push_back(sv.substr(pos, next_delim_pos - pos));

		if (next_delim_pos == std::string_view::npos) {
			break;
		}

		pos = next_delim_pos + delim.size();
	}

	return res;
}

auto read_departures()
{
	std::vector<std::pair<wuint128, wuint128>> departures;

	std::string line;

	std::cin >> line;

	std::uint32_t remainder = 0;

	for (auto token : split(line, ",")) {
		if (token != "x") {
			std::uint32_t p = std::stoi(std::string(token));

			auto delta = remainder % p;
			delta = delta ? p - delta : 0;

			departures.push_back({wuint128(delta), wuint128(p)});
		}

		++remainder;
	}

	return departures;
}

constexpr std::pair<wuint128, wuint128> bezout_coeff(const wuint128 &a, const wuint128 &b)
{
	wuint128 old_r = a;
	wuint128 r = b;
	wuint128 old_s(1);
	wuint128 s(0);
	wuint128 old_t(0);
	wuint128 t(1);

	while (r != 0) {
		wuint128 quotient = idiv(old_r, r);

		old_r = std::exchange(r, old_r - quotient * r);
		old_s = std::exchange(s, old_s - quotient * s);
		old_t = std::exchange(t, old_t - quotient * t);
	}

	return {old_s, old_t};
}

int main()
{
	int start_time = 0;

	std::cin >> start_time;

	auto departures = read_departures();

	std::cout << std::format("{} departures read\n", departures.size());

	auto [app, pp] = departures.front();

	for (auto [ap, p] : departures | std::views::drop(1)) {
		auto [m, n] = bezout_coeff(pp, p);

		auto res = ap * m * pp + app * n * p;

		pp *= p;

		res = imod(res, pp);

		if (res.is_negative()) {
			res += pp;
		}

		app = res;
	}

	std::cout << app << '\n';
}
