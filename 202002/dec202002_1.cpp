//
// Advent of Code 2020, day 2, part one
//

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

bool matches_policy(const std::string &line)
{
	std::istringstream ss(line);

	std::size_t min = 0;
	std::size_t max = 0;
	char sep = '\0';
	char ch = '\0';
	std::string pwd;

	ss >> min >> sep >> max >> ch >> sep >> pwd;

	std::size_t num_ch = std::ranges::count(pwd, ch);

	return num_ch >= min && num_ch <= max;
}

int main()
{
	std::size_t num_valid = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		num_valid += static_cast<std::size_t>(matches_policy(line));
	}

	std::cout << num_valid << '\n';
}
