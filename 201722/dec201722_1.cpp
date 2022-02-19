//
// Advent of Code 2017, day 22, part one
//

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct PairHash {
	template<typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2> &p) const noexcept
	{
		std::size_t h1 = std::hash<T1>()(p.first);
		std::size_t h2 = std::hash<T2>()(p.second);
		return (17 * 37 + h1) * 37 + h2;
	}
};

using Infected = std::unordered_set<std::pair<int, int>, PairHash>;

auto read_map()
{
	std::vector<std::string> map;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); ) {
		map.push_back(std::move(line));
	}

	return map;
}

auto get_infected_from_map(const auto &map)
{
	Infected infected;

	int mid_y = map.size() / 2;
	int mid_x = map[0].size() / 2;

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == '#') {
				infected.insert({x - mid_x, mid_y - y});
			}
		}
	}

	return infected;
}

int main()
{
	auto map = read_map();

	auto infected = get_infected_from_map(map);

	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 1;

	std::size_t num_became_infected = 0;

	for (std::size_t bursts = 0; bursts != 10'000; ++bursts) {
		if (auto [it, success] = infected.insert({x, y}); !success) {
			dx = std::exchange(dy, -dx);

			infected.erase(it);
		}
		else {
			dy = std::exchange(dx, -dy);

			++num_became_infected;
		}

		x += dx;
		y += dy;
	}

	std::cout << num_became_infected << '\n';
}
