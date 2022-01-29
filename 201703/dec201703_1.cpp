//
// Advent of Code 2017, day 3, part one
//

#include <cstdlib>
#include <iostream>

int main()
{
	constexpr long target_square = 368078;

	long radius = 1;
	long base = 2;

	while (target_square - base >= 8 * radius) {
		base += 8 * radius;
		++radius;
	}

	// At radius r, the Manhattan distance oscillates between r and
	// 2 * r, starting at 2 * r - 1, going down. The expression
	//
	//     b - std::abs(i % (2 * (b - a)) - (b - a))
	//
	// oscillates between a and b. Substituting the limits and correcting
	// for the starting position, we get:
	std::cout << 2 * radius - std::abs(((target_square - base + radius + 1) % (2 * radius)) - radius) << '\n';
}
