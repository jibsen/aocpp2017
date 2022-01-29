//
// Advent of Code 2017, day 3, part two
//

#include <iostream>
#include <unordered_map>

struct PairHash {
	template<typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2> &p) const noexcept
	{
		std::size_t h1 = std::hash<T1>()(p.first);
		std::size_t h2 = std::hash<T2>()(p.second);

		return (17 * 37 + h1) * 37 + h2;
	}
};

using Grid = std::unordered_map<std::pair<int, int>, long, PairHash>;

long sum_adjacent(Grid &grid, int x, int y)
{
	long sum = 0;

	for (int dy : {-1, 0, 1}) {
		for (int dx : {-1, 0, 1}) {
			if (dx == 0 && dy == 0) {
				continue;
			}

			sum += grid[{x + dx, y + dy}];
		}
	}

	return sum;
}

int main()
{
	constexpr long target_square = 368078;

	Grid grid;

	grid[{0, 0}] = 1;

	auto fill_and_check = [&](int x, int y) {
		long sum = sum_adjacent(grid, x, y);

		grid[{x, y}] = sum;

		if (sum > target_square) {
			std::cout << sum << '\n';
			exit(0);
		}
	};

	for (int x = 1, y = 0, radius = 1; ; ++radius) {
		for (; y > -radius; --y) {
			fill_and_check(x, y);
		}

		for (; x > -radius; --x) {
			fill_and_check(x, y);
		}

		for (; y < radius; ++y) {
			fill_and_check(x, y);
		}

		for (; x <= radius; ++x) {
			fill_and_check(x, y);
		}
	}
}
