//
// Advent of Code 2017, day 23, part two
//

// Looking through the program, we can see it starts at b = 105'700 and
// loops in increments of 17 up to and including b equal to 122'700.
//
// For these 1001 steps, it calculates all products of d and e in the range
// from 2 to b. If, for any of them, d * e is equal to b (i.e. b is
// composite), it increments h.
//
// So it computes in h the number of composite numbers out of those 1001.

#include <algorithm>
#include <array>
#include <iostream>

int main()
{
	static constexpr std::array small_primes = {
		  2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
		 31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
		 73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
		127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
		179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
		233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
		283, 293, 307, 311, 313, 317, 331, 337, 347, 349
	};

	long num_composite = 0;

	for (long b = 105'700; b <= 122'700; b += 17) {
		num_composite += std::ranges::any_of(small_primes,
			[&b](long prime) {
				return (b % prime) == 0;
			}
		);
	}

	std::cout << num_composite << '\n';
}
