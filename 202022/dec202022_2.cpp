//
// Advent of Code 2020, day 22, part two
//

#include <array>
#include <deque>
#include <iostream>
#include <ranges>
#include <unordered_set>
#include <string>

struct ArrayHash {
	template<typename T, std::size_t size>
	std::size_t operator()(const std::array<T, size> &array) const noexcept
	{
		std::size_t hash = 17;
		for (const auto &elem : array) {
			hash = hash * 37 + std::hash<T>()(elem);
		}
		return hash;
	}
};

using Player = std::deque<int>;

auto read_starting_decks()
{
	Player player1;
	Player player2;

	std::string line;

	std::getline(std::cin, line);

	while (std::getline(std::cin, line) && !line.empty()) {
		player1.push_back(std::stoi(line));
	}

	std::getline(std::cin, line);

	while (std::getline(std::cin, line) && !line.empty()) {
		player2.push_back(std::stoi(line));
	}

	return std::make_pair(player1, player2);
}

std::size_t score(const Player &player)
{
	std::size_t score = 0;

	for (std::size_t idx = 1; auto card : player | std::views::reverse) {
		score += card * idx++;
	}

	return score;
}

// While perhaps not needed for a game this size, store the player decks
// seen in this more compact form rather than an unordered set of deques
using CompactPlayer = std::array<std::uint8_t, 50>;

auto compact(const Player &p)
{
	CompactPlayer c = {};

	std::ranges::copy(p, c.begin());

	return c;
}

int play_game(Player &p1, Player &p2)
{
	std::unordered_set<CompactPlayer, ArrayHash> seen1;
	std::unordered_set<CompactPlayer, ArrayHash> seen2;

	while (!(p1.empty() || p2.empty())) {
		if (auto [it, success] = seen1.insert(compact(p1)); !success) {
			return 1;
		}
		if (auto [it, success] = seen2.insert(compact(p2)); !success) {
			return 1;
		}

		if (p1.front() < p1.size() && p2.front() < p2.size()) {
			Player sub_p1;
			Player sub_p2;

			sub_p1.insert(sub_p1.end(), p1.begin() + 1, p1.begin() + 1 + p1.front());
			sub_p2.insert(sub_p2.end(), p2.begin() + 1, p2.begin() + 1 + p2.front());

			if (play_game(sub_p1, sub_p2) == 1) {
				p1.push_back(p1.front());
				p1.pop_front();
				p1.push_back(p2.front());
				p2.pop_front();
			}
			else {
				p2.push_back(p2.front());
				p2.pop_front();
				p2.push_back(p1.front());
				p1.pop_front();
			}

			continue;
		}

		if (p1.front() > p2.front()) {
			p1.push_back(p1.front());
			p1.pop_front();
			p1.push_back(p2.front());
			p2.pop_front();
		}
		else {
			p2.push_back(p2.front());
			p2.pop_front();
			p2.push_back(p1.front());
			p1.pop_front();
		}
	}

	return p1.empty() ? 2 : 1;
}

int main()
{
	auto [player1, player2] = read_starting_decks();

	std::cout << score(play_game(player1, player2) == 1 ? player1 : player2) << '\n';
}
