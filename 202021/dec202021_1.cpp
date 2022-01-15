//
// Advent of Code 2020, day 21, part one
//

#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

auto read_foods()
{
	std::vector<std::pair<std::set<std::string>, std::vector<std::string>>> foods;

	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream ss(line);

		std::set<std::string> names;
		std::vector<std::string> allergens;

		for (std::string token; ss >> token; ) {
			if (token.starts_with('(')) {
				while (ss >> token) {
					token.pop_back();
					allergens.push_back(std::move(token));
				}

				break;
			}

			names.insert(std::move(token));
		}

		std::ranges::sort(allergens);

		foods.emplace_back(std::move(names), std::move(allergens));
	}

	return foods;
}

int main()
{
	auto foods = read_foods();

	std::cout << std::format("{} foods read\n", foods.size());

	std::unordered_map<std::string, std::vector<int>> foods_with_allergen;

	for (int i = 0; i < foods.size(); ++i) {
		for (const auto &allergen : foods[i].second) {
			foods_with_allergen[allergen].push_back(i);
		}
	}

	for (;;) {
		std::string match_ingredient;
		std::string match_allergen;

		// For each allergen, intersect the ingredient lists of the
		// foods that are known to contain it. If there is only one
		// common ingredient, it must be the allergen.

		for (auto &[allergen, food_ids] : foods_with_allergen) {
			std::set<std::string> common_ingredients = foods[food_ids.front()].first;

			for (int id : food_ids | std::views::drop(1)) {
				if (common_ingredients.size() == 1) {
					break;
				}

				std::set<std::string> temp = std::move(common_ingredients);
				common_ingredients.clear();

				std::ranges::set_intersection(temp, foods[id].first,
					std::inserter(common_ingredients, common_ingredients.end())
				);
			}

			if (common_ingredients.size() == 1) {
				std::cout << std::format("{} is {}\n", *common_ingredients.begin(), allergen);
				match_ingredient = *common_ingredients.begin();
				match_allergen = allergen;
				break;
			}
		}

		if (match_ingredient.empty()) {
			break;
		}

		for (auto &[names, allergens] : foods) {
			names.erase(match_ingredient);
			std::erase(allergens, match_allergen);
		}

		foods_with_allergen.erase(match_allergen);
	}

	std::cout << std::format("{} unmatched allergens\n", foods_with_allergen.size());

	auto view = foods | std::views::transform([](const auto &food) { return food.first.size(); }) | std::views::common;

	std::cout << std::accumulate(view.begin(), view.end(), 0ULL) << '\n';
}
