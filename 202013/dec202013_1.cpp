//
// Advent of Code 2020, day 13, part one
//

#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

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
	std::vector<int> departures;

	std::string line;

	std::cin >> line;

	for (auto token : split(line, ",")) {
		if (token != "x") {
			departures.push_back(std::stoi(std::string(token)));
		}
	}

	return departures;
}

int main()
{
	int start_time = 0;

	std::cin >> start_time;

	auto departures = read_departures();

	std::cout << std::format("{} departures read\n", departures.size());

	int min_delta = std::numeric_limits<int>::max();
	int min_delta_departure = -1;

	for (auto dep : departures) {
		auto delta = start_time % dep;
		delta = delta ? dep - delta : 0;

		if (delta < min_delta) {
			min_delta = delta;
			min_delta_departure = dep;
		}
	}

	std::cout << min_delta * min_delta_departure << '\n';
}
