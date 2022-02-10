//
// Advent of Code 2017, day 13, part one
//

#include <cmath>
#include <iostream>

int main()
{
	int depth = 0;
	int range = 0;

	int severity = 0;

	for (char sep = '\0'; std::cin >> depth >> sep >> range && sep == ':'; ) {
		int delta = range - 1;

		if (delta - std::abs(depth % (2 * delta) - delta) == 0) {
			severity += depth * range;
		}
	}

	std::cout << severity << '\n';
}
