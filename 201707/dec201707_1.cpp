//
// Advent of Code 2017, day 7, part one
//

#include <algorithm>
#include <iostream>
#include <ranges>
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

		std::vector<std::string> children;

		for (std::string token; is >> token; ) {
			if (token == "->") {
				continue;
			}

			if (token.ends_with(',')) {
				token.pop_back();
			}

			children.push_back(std::move(token));
		}

		adj.emplace(std::move(name), std::make_pair(weight, std::move(children)));
	}

	return adj;
}

int main()
{
	auto adj = read_list();

	// Mark all non-root nodes by setting their weight to -1
	for (const auto &[weight, children] : adj | std::views::values) {
		for (const auto &name : children) {
			adj[name].first = -1;
		}
	}

	auto root = std::ranges::find_if(adj,
		[](const auto &p) {
			return p.second.first != -1;
		}
	);

	if (root != adj.end()) {
		std::cout << root->first << '\n';
	}
}
