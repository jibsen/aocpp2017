//
// Advent of Code 2017, day 15, part one
//

#include <iostream>
#include <random>

int main()
{
	std::linear_congruential_engine<std::uint_fast32_t, 16807, 0, 2147483647> a;
	std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> b;

	a.seed(289);
	b.seed(629);

	unsigned long count = 0;

	for (unsigned long i = 0; i < 40'000'000L; ++i) {
		if ((a() & 0xFFFF) == (b() & 0xFFFF)) {
			++count;
		}
	}

	std::cout << count << '\n';
}
