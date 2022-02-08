//
// Advent of Code 2017, day 11, part one and two
//

// We notice that the distance to any hexagon that is dx away in the x
// direction, and less than or equal dx away in the y direction, is the same.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

auto split(std::string_view s, std::string_view delims)
{
	std::vector<std::string_view> res;

	std::string_view::size_type pos = 0;

	for (;;) {
		pos = s.find_first_not_of(delims, pos);

		if (pos == std::string_view::npos) {
			break;
		}

		auto start = pos;

		pos = s.find_first_of(delims, pos);

		res.push_back(s.substr(start, pos - start));

		if (pos == std::string_view::npos) {
			break;
		}
	}

	return res;
}

int hexagonal_distance(int x1, int y1, int x2, int y2)
{
	int dx = std::abs(x2 - x1) / 2;
	int dy = std::abs(y2 - y1);

	return dx + std::max(0, dy - dx) / 2;
}

int main()
{
	static const std::unordered_map<std::string_view, std::pair<int, int>> lookup = {
		{ "n", { 0, 2 } }, { "ne", { 2, 1 } }, { "se", { 2, -1 } },
		{ "s", { 0, -2 } }, { "sw", { -2, -1 } }, { "nw", { -2, 1 } }
	};

	std::string line;

	std::getline(std::cin, line);

	auto tokens = split(line, ",.");

	int x = 0;
	int y = 0;
	int max_distance = 0;

	for (auto token : tokens) {
		auto [dx, dy] = lookup.at(token);

		x += dx;
		y += dy;

		max_distance = std::max(max_distance, hexagonal_distance(0, 0, x, y));
	}

	std::cout << "final distance: " << hexagonal_distance(0, 0, x, y) << '\n';
	std::cout << "max distance: " << max_distance << '\n';
}
