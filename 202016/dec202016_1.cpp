//
// Advent of Code 2020, day 16, part one
//

#include <format>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

auto read_rules()
{
	std::vector<std::tuple<int, int, int, int>> rules;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); ) {
		std::istringstream ss(line.substr(line.find(':') + 1));

		std::string token;
		char sep = '\0';
		int l1 = 0;
		int r1 = 0;
		int l2 = 0;
		int r2 = 0;

		ss >> l1 >> sep >> r1 >> token >> l2 >> sep >> r2;

		rules.emplace_back(l1, r1, l2, r2);
	}

	return rules;
}

auto read_your_ticket()
{
	std::string line;

	do {
		std::getline(std::cin, line);
	} while (!line.starts_with("your"));

	std::getline(std::cin, line);

	std::istringstream ss(line);

	std::vector<int> ticket;
	int field = 0;

	for (char sep = ','; sep == ',' && ss >> field; ss >> sep) {
		ticket.push_back(field);
	}

	return ticket;
}


auto read_nearby_tickets()
{
	std::vector<std::vector<int>> tickets;
	std::string line;

	do {
		std::getline(std::cin, line);
	} while (!line.starts_with("nearby"));

	while (std::getline(std::cin, line)) {
		std::istringstream ss(line);

		std::vector<int> ticket;
		int field = 0;

		for (char sep = ','; sep == ',' && ss >> field; ss >> sep) {
			ticket.push_back(field);
		}

		tickets.push_back(std::move(ticket));
	}

	return tickets;
}

int main()
{
	auto rules = read_rules();
	[[maybe_unused]] auto your_ticket = read_your_ticket();
	auto nearby_tickets = read_nearby_tickets();

	std::cout << std::format("{} rules read\n", rules.size());
	std::cout << std::format("{} nearby tickets read\n", nearby_tickets.size());

	std::vector<bool> valid_numbers(1000, false);

	for (auto [l1, r1, l2, r2] : rules) {
		for (int i = l1; i <= r1; ++i) {
			valid_numbers[i] = true;
		}
		for (int i = l2; i <= r2; ++i) {
			valid_numbers[i] = true;
		}
	}

	auto invalid_fields = nearby_tickets
	                    | std::views::join
	                    | std::views::filter([&](int field) { return !valid_numbers[field]; })
	                    | std::views::common;

	std::cout << std::accumulate(invalid_fields.begin(), invalid_fields.end(), 0L) << '\n';
}
