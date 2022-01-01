//
// Advent of Code 2020, day 6, part one
//

#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

using Group = std::vector<std::string>;

auto read_groups()
{
	std::vector<Group> groups;
	Group group;

	for (std::string line; std::getline(std::cin, line); ) {
		if (line.empty()) {
			groups.push_back(std::move(group));
			group.clear();
			continue;
		}

		group.push_back(std::move(line));
	}

	if (!group.empty()) {
		groups.push_back(std::move(group));
	}

	return groups;
}

std::size_t num_yes_answers(const Group &grp)
{
	std::unordered_set<char> questions;

	for (const auto &person : grp) {
		for (auto question : person) {
			questions.insert(question);
		}
	}

	return questions.size();
}

int main()
{
	auto groups = read_groups();

	auto view = groups | std::views::transform(num_yes_answers) | std::views::common;

	std::cout << std::accumulate(view.begin(), view.end(), 0ULL) << '\n';
}
