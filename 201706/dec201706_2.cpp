//
// Advent of Code 2017, day 6, part two
//

#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <unordered_map>

struct RangeHash {
	template<std::ranges::forward_range Range>
	std::size_t operator()(const Range &range) const noexcept
	{
		std::size_t hash = 17;
		for (const auto &elem : range) {
			hash = hash * 37 + std::hash<typename Range::value_type>()(elem);
		}
		return hash;
	}
};

int main()
{
	std::array banks = { 14, 0, 15, 12, 11, 11, 3, 5, 1, 6, 8, 4, 9, 1, 8, 4 };
	// std::array banks = { 0, 2, 7, 0 };

	std::unordered_map<decltype(banks), int, RangeHash> seen;

	seen.insert({banks, 0});

	for (int cycles = 1; ; ++cycles) {
		auto it = std::max_element(banks.begin(), banks.end());

		int blocks = *it;
		*it++ = 0;

		for (; blocks != 0; blocks--) {
			if (it == banks.end()) {
				it = banks.begin();
			}

			*it++ += 1;
		}

		if (auto [seen_it, success] = seen.insert({banks, cycles}); !success) {
			std::cout << cycles - seen_it->second << '\n';
			break;
		}
	}
}
