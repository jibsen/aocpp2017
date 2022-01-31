//
// Advent of Code 2017, day 5, part two
//

#include <iostream>
#include <iterator>
#include <vector>

int main()
{
	std::vector<long> offsets(std::istream_iterator<long>{std::cin},
	                         std::istream_iterator<long>{});

	long steps = 0;

	for (long i = 0; i >= 0 && i < offsets.size(); ++steps) {
		long offset = offsets[i];

		offsets[i] += offset >= 3 ? -1 : 1;

		i += offset;
	}

	std::cout << steps << '\n';
}
