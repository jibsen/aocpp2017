//
// Advent of Code 2017, day 1, part one
//

#include <iostream>
#include <functional>
#include <numeric>
#include <string>

int main()
{
	std::string digits;

	std::cin >> digits;

	std::cout << std::transform_reduce(
		digits.begin(), digits.end() - 1, digits.begin() + 1,
		std::size_t(digits.front() == digits.back() ? digits.front() - '0' : 0),
		std::plus(),
		[](char l, char r) { return l == r ? l - '0' : 0; }
	);
}
