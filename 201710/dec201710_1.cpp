//
// Advent of Code 2017, day 10, part one
//

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

auto read_lengths()
{
	std::vector<int> lengths;
	int length = 0;

	for (char sep = ','; sep == ',' && std::cin >> length; std::cin >> sep) {
		lengths.push_back(length);
	}

	return lengths;
}

void circular_reverse(std::span<std::uint8_t> sp, int i, int j)
{
	for (--j; i < j; ++i, --j) {
		std::swap(sp[i % sp.size()], sp[j % sp.size()]);
	}
}

int main()
{
	const auto lengths = read_lengths();

	std::array<std::uint8_t, 256> list;

	std::iota(list.begin(), list.end(), 0);

	int pos = 0;
	int skip = 0;

	for (auto length : lengths) {
		circular_reverse(list, pos, pos + length);

		pos = (pos + length + skip++) % list.size();
	}

	std::cout << list[0] * list[1] << '\n';
}
