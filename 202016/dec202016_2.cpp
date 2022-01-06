//
// Advent of Code 2020, day 16, part two
//

#include <algorithm>
#include <format>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using Rule = std::tuple<std::string, int, int, int, int>;

auto read_rules()
{
	std::vector<Rule> rules;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); ) {
		std::string name = line.substr(0, line.find(':'));

		std::istringstream ss(line.substr(line.find(':') + 1));

		std::string token;
		char sep = '\0';
		int l1 = 0;
		int r1 = 0;
		int l2 = 0;
		int r2 = 0;

		ss >> l1 >> sep >> r1 >> token >> l2 >> sep >> r2;

		rules.emplace_back(std::move(name), l1, r1, l2, r2);
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

void remove_invalid_tickets(std::vector<std::vector<int>> &tickets, const std::vector<Rule> &rules)
{
	std::vector<bool> valid_numbers(1000, false);

	for (const auto &[name, l1, r1, l2, r2] : rules) {
		for (int i = l1; i <= r1; ++i) {
			valid_numbers[i] = true;
		}
		for (int i = l2; i <= r2; ++i) {
			valid_numbers[i] = true;
		}
	}

	auto is_invalid = [&](const auto &ticket) {
		return std::ranges::any_of(ticket, [&](int field) { return !valid_numbers[field]; });
	};

	std::erase_if(tickets, is_invalid);
}

auto get_candiate_ids_for_rules(const std::vector<std::vector<int>> &tickets, const std::vector<Rule> &rules)
{
	std::vector<std::vector<int>> candidate_ids_for_rules;

	candidate_ids_for_rules.reserve(rules.size());

	for (const auto &[name, l1, r1, l2, r2] : rules) {
		std::vector<int> valid_candidates;

		for (int id = 0; id < tickets[0].size(); ++id) {
			auto id_is_valid = [&](const auto &ticket) {
				return (ticket[id] >= l1 && ticket[id] <= r1)
				    || (ticket[id] >= l2 && ticket[id] <= r2);
			};

			if (std::ranges::all_of(tickets, id_is_valid)) {
				valid_candidates.push_back(id);
			}
		}

		candidate_ids_for_rules.push_back(std::move(valid_candidates));
	}

	return candidate_ids_for_rules;
}

int main()
{
	auto rules = read_rules();
	auto your_ticket = read_your_ticket();
	auto nearby_tickets = read_nearby_tickets();

	std::cout << std::format("{} rules read\n", rules.size());
	std::cout << std::format("{} nearby tickets read\n", nearby_tickets.size());

	remove_invalid_tickets(nearby_tickets, rules);

	std::cout << std::format("{} valid nearby tickets\n", nearby_tickets.size());

	auto candidate_ids_for_rules = get_candiate_ids_for_rules(nearby_tickets, rules);

	long long product_of_departure_fields = 1;

	for (;;) {
		int rule_with_unique_id = -1;

		for (int i = 0; i < candidate_ids_for_rules.size(); ++i) {
			if (candidate_ids_for_rules[i].size() == 1) {
				rule_with_unique_id = i;
				break;
			}
		}

		if (rule_with_unique_id == -1) {
			break;
		}

		int id = candidate_ids_for_rules[rule_with_unique_id][0];

		if (std::get<0>(rules[rule_with_unique_id]).starts_with("departure")) {
			product_of_departure_fields *= your_ticket[id];
		}

		for (auto &candidates : candidate_ids_for_rules) {
			std::erase(candidates, id);
		}
	}

	std::cout << product_of_departure_fields << '\n';
}
