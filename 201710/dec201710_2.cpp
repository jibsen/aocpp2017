//
// Advent of Code 2017, day 10, part two
//

#include <algorithm>
#include <array>
#include <cstdint>
#include <format>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <span>
#include <string>
#include <vector>

auto read_lengths()
{
	std::string line;

	std::getline(std::cin, line);

	std::vector<int> lengths;
	lengths.reserve(line.size());

	std::ranges::transform(line, std::back_inserter(lengths),
		[](char c) { return static_cast<unsigned char>(c); });

	lengths.insert(lengths.end(), {17, 31, 73, 47, 23});

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

	for (int round = 0; round < 64; ++round) {
		for (auto length : lengths) {
			circular_reverse(list, pos, pos + length);

			pos = (pos + length + skip++) % list.size();
		}
	}

	for (std::size_t base = 0; base < 256; base += 16) {
		std::uint8_t hash = std::accumulate(&list[base], &list[base + 16],
		                                    std::uint8_t(0), std::bit_xor());

		std::cout << std::format("{:02x}", hash);
	}

	std::cout << '\n';
}
