//
// Advent of Code 2017, day 17, part two
//

// We note that we only have to keep track of the position of the zero
// and the values inserted right after it. Furthermore we always insert
// after the next position, so zero will always be the first element.

#include <iostream>

int main()
{
	constexpr int delta = 316;

	long pos = 0;

	long list_size = 1;
	long number_after_zero = -1;

	for (long i = 1; i <= 50'000'000L; ++i) {
		pos = ((pos + delta) % list_size) + 1;

		if (pos == 1) {
			number_after_zero = i;
		}

		++list_size;
	}

	std::cout << number_after_zero << '\n';
}
