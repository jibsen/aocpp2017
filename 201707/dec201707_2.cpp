//
// Advent of Code 2017, day 7, part two
//

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <ranges>
#include <span>
#include <sstream>
#include <string>
#include <unordered_map>

using Adj = std::unordered_map<std::string, std::pair<int, std::vector<std::string>>>;

Adj read_list()
{
	Adj adj;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); ) {
		std::istringstream is(line);

		std::string name;
		int weight = 0;
		char sep = '\0';

		is >> name >> sep >> weight >> sep;

		std::vector<std::string> neighbors;

		for (std::string token; is >> token; ) {
			if (token == "->") {
				continue;
			}

			if (token.ends_with(',')) {
				token.pop_back();
			}

			neighbors.push_back(std::move(token));
		}

		adj.emplace(std::move(name), std::make_pair(weight, std::move(neighbors)));
	}

	return adj;
}

std::pair<std::size_t, int> find_adjustment(std::span<const int> sp)
{
	auto it = std::ranges::adjacent_find(sp, std::not_equal_to());

	if (it == sp.end()) {
		return {0, 0};
	}

	if (it != sp.begin()) {
		++it;

		return {std::distance(sp.begin(), it), sp.front() - *it};
	}
	else {
		if (*it == sp.back()) {
			++it;
		}

		return {std::distance(sp.begin(), it), sp.back() - *it};
	}
}

int adjust_tower_weight(Adj &adj, const std::string &root)
{
	const auto &[weight, children] = adj[root];

	if (children.empty()) {
		return weight;
	}

	std::vector<int> child_weights;
	int child_sum = 0;

	for (const auto &child : children) {
		int child_weight = adjust_tower_weight(adj, child);

		child_weights.push_back(child_weight);

		child_sum += child_weight;
	}

	auto [child_to_adjust, adjustment] = find_adjustment(child_weights);

	if (adjustment != 0) {
		int child_weight = adj[children[child_to_adjust]].first;

		std::cout << children[child_to_adjust] << " weight " << child_weight << " needs adjustment of " << adjustment << '\n';

		adj[children[child_to_adjust]].first += adjustment;
		child_sum += adjustment;
	}

	return weight + child_sum;
}

int main()
{
	auto adj = read_list();

	adjust_tower_weight(adj, "rqwgj");

	return 0;
}
