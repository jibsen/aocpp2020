//
// Advent of Code 2020, day 2, part two
//

#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

bool matches_policy(const std::string &line)
{
	std::istringstream ss(line);

	std::size_t pos1 = 0;
	std::size_t pos2 = 0;
	char sep = '\0';
	char ch = '\0';
	std::string pwd;

	ss >> pos1 >> sep >> pos2 >> ch >> sep >> pwd;

	return (pwd.at(pos1 - 1) == ch) != (pwd.at(pos2 - 1) == ch);
}

int main()
{
	std::size_t num_valid = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		num_valid += static_cast<std::size_t>(matches_policy(line));
	}

	std::cout << num_valid << '\n';
}
