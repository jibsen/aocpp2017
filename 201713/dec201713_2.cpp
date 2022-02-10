//
// Advent of Code 2017, day 13, part two
//

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

auto read_firewall()
{
	std::vector<std::pair<int, int>> res;

	int depth = 0;
	int range = 0;

	for (char sep = '\0'; std::cin >> depth >> sep >> range && sep == ':'; ) {
		res.emplace_back(depth, range);
	}

	return res;
}

int main()
{
	auto firewall = read_firewall();

	for (long start = 0; ; ++start) {
		bool safe = true;

		for (auto [depth, range] : firewall) {
			int delta = range - 1;

			if (delta - std::abs((start + depth) % (2 * delta) - delta) == 0) {
				safe = false;
				break;
			}
		}

		if (safe) {
			std::cout << start << '\n';
			break;
		}
	}
}
