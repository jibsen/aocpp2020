//
// Advent of Code 2020, day 22, part one
//

#include <deque>
#include <iostream>
#include <ranges>
#include <string>

auto read_starting_decks()
{
	std::deque<int> player1;
	std::deque<int> player2;

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

std::size_t score(const std::deque<int> &player)
{
	std::size_t score = 0;

	for (std::size_t idx = 1; auto card : player | std::views::reverse) {
		score += card * idx++;
	}

	return score;
}

int main()
{
	auto [player1, player2] = read_starting_decks();

	while (!(player1.empty() || player2.empty())) {
		if (player1.front() > player2.front()) {
			player1.push_back(player1.front());
			player1.pop_front();
			player1.push_back(player2.front());
			player2.pop_front();
		}
		else {
			player2.push_back(player2.front());
			player2.pop_front();
			player2.push_back(player1.front());
			player1.pop_front();
		}
	}

	std::cout << score(player1.empty() ? player2 : player1) << '\n';
}
