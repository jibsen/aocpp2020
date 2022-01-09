//
// Advent of Code 2020, day 19, part one
//

#include <algorithm>
#include <format>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Rule {
	std::vector<std::vector<int>> subrules;
	char match = '\0';
};

auto read_rules()
{
	std::unordered_map<int, Rule> rules;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); ) {
		Rule rule;

		int id = std::stoi(line);

		std::istringstream ss(line.substr(line.find(':') + 1));

		std::vector<int> subrule;

		for (std::string token; ss >> token; ) {
			if (token.starts_with('"')) {
				rule.match = token[1];
				break;
			}

			if (token == "|") {
				rule.subrules.push_back(std::move(subrule));
				subrule.clear();
				continue;
			}

			subrule.push_back(std::stoi(token));
		}

		if (!subrule.empty()) {
			rule.subrules.push_back(std::move(subrule));
		}

		rules.emplace(id, std::move(rule));
	}

	return rules;
}

struct RuleMatcher {
	explicit RuleMatcher(std::unordered_map<int, Rule> rules) : rules(std::move(rules)) {}

	bool matches_rules(std::string_view message) const;

private:
	const std::unordered_map<int, Rule> rules;

	bool matches_rule(std::string_view message, int &pos, const Rule &rule) const;
	bool matches_subrule(std::string_view message, int &pos, const std::vector<int> &subrule) const;
	bool matches_char(std::string_view message, int &pos, const Rule &rule) const;
};

bool RuleMatcher::matches_rules(std::string_view message) const
{
	int pos = 0;

	return matches_rule(message, pos, rules.at(0)) && pos == message.size();
}

bool RuleMatcher::matches_rule(std::string_view message, int &pos, const Rule &rule) const
{
	if (rule.subrules.empty()) {
		return matches_char(message, pos, rule);
	}

	int start = pos;

	for (const auto &subrule : rule.subrules) {
		if (matches_subrule(message, pos, subrule)) {
			return true;
		}

		pos = start;
	}

	return false;
}

bool RuleMatcher::matches_subrule(std::string_view message, int &pos, const std::vector<int> &subrule) const
{
	int start = pos;

	for (int id : subrule) {
		if (!matches_rule(message, pos, rules.at(id))) {
			pos = start;
			return false;
		}
	}

	return true;
}

bool RuleMatcher::matches_char(std::string_view message, int &pos, const Rule &rule) const
{
	if (pos != message.size() && message[pos] == rule.match) {
		++pos;
		return true;
	}

	return false;
}

int main()
{
	const auto rules = read_rules();

	std::vector<std::string> messages(
		std::istream_iterator<std::string>{std::cin},
		std::istream_iterator<std::string>{}
	);

	std::cout << std::format("{} rules read\n", rules.size());
	std::cout << std::format("{} messages read\n", messages.size());

	RuleMatcher matcher(rules);

	auto matches_rules = [&matcher](const std::string &message) {
		return matcher.matches_rules(message);
	};

	std::cout << std::ranges::count_if(messages, matches_rules) << '\n';
}
