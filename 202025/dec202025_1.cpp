//
// Advent of Code 2020, day 25, part one
//

#include <iostream>

constexpr unsigned long long modexp(unsigned long long a,
                                    unsigned long long k,
                                    unsigned long long n)
{
	unsigned long long res = 1;

	for (; k > 0; k /= 2) {
		if (k % 2) {
			res = (res * a) % n;
		}

		a = (a * a) % n;
	}

	return res;
}

int main()
{
	constexpr unsigned long long p = 20201227;

	unsigned long long pub_card = 0;
	unsigned long long pub_door = 0;

	std::cin >> pub_card >> pub_door;

	unsigned long long loop_card = 0;

	for (unsigned long long value = 1; value != pub_card; ++loop_card) {
		value = (7 * value) % p;
	}

	unsigned long long loop_door = 0;

	for (unsigned long long value = 1; value != pub_door; ++loop_door) {
		value = (7 * value) % p;
	}

	std::cout << loop_card << '\n';
	std::cout << loop_door << '\n';

	std::cout << modexp(pub_door, loop_card, p) << '\n';
	std::cout << modexp(pub_card, loop_door, p) << '\n';
}
