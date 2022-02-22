//
// Advent of Code 2017, day 24, part one
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
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

using Adj = std::unordered_map<int, std::vector<int>>;

auto read_components()
{
	Adj adj;

	int side1 = 0;
	int side2 = 0;
	char sep = '\0';

	while (std::cin >> side1 >> sep >> side2) {
		adj[side1].push_back(side2);
		adj[side2].push_back(side1);
	}

	return adj;
}

long find_best_strength(Adj &adj, long strength, int in_pins)
{
	static std::unordered_set<std::pair<int, int>, PairHash> used;

	long best_strength = strength;

	for (int out_pins : adj[in_pins]) {
		if (auto [it, success] = used.insert(std::minmax(in_pins, out_pins)); success) {

			best_strength = std::max(best_strength, find_best_strength(adj, strength + in_pins + out_pins, out_pins));

			used.erase(it);
		}
	}

	return best_strength;
}

int main()
{
	auto adj = read_components();

	std::cout << find_best_strength(adj, 0, 0) << '\n';
}
