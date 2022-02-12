//
// Advent of Code 2017, day 15, part two
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

	for (unsigned long i = 0; i < 5'000'000L; ++i) {
		std::uint_fast32_t next_a = 0;
		std::uint_fast32_t next_b = 0;

		do {
			next_a = a();
		} while (next_a & 0b0011);

		do {
			next_b = b();
		} while (next_b & 0b0111);

		if ((next_a & 0xFFFF) == (next_b & 0xFFFF)) {
			++count;
		}
	}

	std::cout << count << '\n';
}
