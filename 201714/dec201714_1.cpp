//
// Advent of Code 2017, day 14, part one
//

#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <iostream>
#include <functional>
#include <numeric>
#include <span>
#include <string>
#include <string_view>
#include <vector>

using List = std::array<std::uint8_t, 256>;

void circular_reverse(std::span<std::uint8_t> sp, int i, int j)
{
	for (--j; i < j; ++i, --j) {
		std::swap(sp[i % sp.size()], sp[j % sp.size()]);
	}
}

List knot_hash_helper(std::string_view sv)
{
	List res;

	std::iota(res.begin(), res.end(), 0);

	int pos = 0;
	int skip = 0;

	for (int round = 0; round < 64; ++round) {
		for (unsigned int length : sv) {
			circular_reverse(res, pos, pos + length);

			pos = (pos + length + skip++) % res.size();
		}
	}

	return res;
}

List knot_hash(std::string s)
{
	s.append({17, 31, 73, 47, 23});

	return knot_hash_helper(s);
}

int main()
{
	const std::string key = "amgozmfv";

	std::size_t num_used = 0;

	for (int i = 0; i < 128; ++i) {
		auto list = knot_hash(key + "-" + std::to_string(i));

		for (std::size_t base = 0; base < 256; base += 16) {
			std::uint8_t hash = std::accumulate(&list[base], &list[base + 16],
			                                    std::uint8_t(0), std::bit_xor());

			num_used += std::popcount(hash);
		}
	}

	std::cout << num_used << '\n';
}
