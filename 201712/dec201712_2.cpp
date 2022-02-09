//
// Advent of Code 2017, day 12, part two
//

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

auto read_graph()
{
	std::vector<std::vector<int>> adj;

	std::string arrow;
	int id = 0;

	while (std::cin >> id >> arrow && arrow == "<->") {
		std::string line;

		std::getline(std::cin, line);

		std::istringstream ss(line);

		int dest = 0;

		std::vector<int> neighbors;

		for (char sep = ','; sep == ',' && ss >> dest; ss >> sep) {
			neighbors.push_back(dest);
		}

		adj.push_back(std::move(neighbors));
	}

	return adj;
}

int main()
{
	auto adj = read_graph();

	std::vector<bool> visited(adj.size());

	std::queue<int> queue;

	std::size_t num_groups = 0;

	for (int i = 0; i < visited.size(); ++i) {
		if (visited[i]) {
			continue;
		}

		++num_groups;

		queue.push(i);
		visited[i] = true;

		while (!queue.empty()) {
			int u = queue.front();
			queue.pop();

			for (auto v : adj[u]) {
				if (!visited[v]) {
					visited[v] = true;

					queue.push(v);
				}
			}
		}
	}

	std::cout << num_groups << '\n';
}
