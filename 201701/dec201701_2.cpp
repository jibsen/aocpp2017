//
// Advent of Code 2017, day 1, part two
//

#include <iostream>
#include <functional>
#include <numeric>
#include <string>

int main()
{
	std::string digits;

	std::cin >> digits;

	std::cout << 2 * std::transform_reduce(
		digits.begin(), digits.begin() + digits.size() / 2, digits.begin() + digits.size() / 2,
		std::size_t(0),
		std::plus(),
		[](char l, char r) { return l == r ? l - '0' : 0; }
	);
}
