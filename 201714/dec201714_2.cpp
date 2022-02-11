//
// Advent of Code 2017, day 14, part two
//

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <functional>
#include <numeric>
#include <queue>
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

void fill(std::vector<std::vector<int>> &map, int start_x, int start_y)
{
	std::queue<std::pair<int, int>> queue;

	queue.push({start_x, start_y});

	while (!queue.empty()) {
		auto [x, y] = queue.front();
		queue.pop();

		static constexpr std::array<std::pair<int, int>, 4> directions = {{
			{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
		}};

		auto inside_map = [&map](int x, int y) {
			return y >= 0 && y < map.size()
			    && x >= 0 && x < map[y].size();
		};

		for (auto [dx, dy] : directions) {
			if (inside_map(x + dx, y + dy)) {
				if (map[y + dy][x + dx] == 1) {
					map[y + dy][x + dx] = 0;
					queue.push({x + dx, y + dy});
				}
			}
		}
	}
}

int main()
{
	std::vector<std::vector<int>> map;

	map.reserve(128);

	const std::string key = "amgozmfv";

	for (int i = 0; i < 128; ++i) {
		auto list = knot_hash(key + "-" + std::to_string(i));

		std::vector<int> row;

		row.reserve(128);

		for (std::size_t base = 0; base < 256; base += 16) {
			std::uint8_t hash = std::accumulate(&list[base], &list[base + 16],
			                                    std::uint8_t(0), std::bit_xor());

			for (std::uint8_t mask = 0b1000'0000; mask; mask >>= 1) {
				row.push_back((hash & mask) ? 1 : 0);
			}
		}

		map.push_back(std::move(row));
	}

	int num_components = 0;

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == 1) {
				++num_components;
				fill(map, x, y);
			}
		}
	}

	std::cout << num_components << '\n';
}
