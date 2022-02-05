//
// Advent of Code 2017, day 8, part one and two
//

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

int main()
{
	std::unordered_map<std::string, int> registers;

	std::string target;
	std::string op;
	int delta = 0;
	std::string token_if;
	std::string lhs;
	std::string relation;
	int rhs = 0;

	int max_value = 0;

	while (std::cin >> target >> op >> delta >> token_if >> lhs >> relation >> rhs && token_if == "if") {
		if (op == "dec") {
			delta = -delta;
		}

		if (relation == "<" && registers[lhs] >= rhs) {
			continue;
		}
		if (relation == "<=" && registers[lhs] > rhs) {
			continue;
		}
		if (relation == ">" && registers[lhs] <= rhs) {
			continue;
		}
		if (relation == ">=" && registers[lhs] < rhs) {
			continue;
		}
		if (relation == "!=" && registers[lhs] == rhs) {
			continue;
		}
		if (relation == "==" && registers[lhs] != rhs) {
			continue;
		}

		registers[target] += delta;

		max_value = std::max(max_value, registers[target]);
	}

	std::cout << "max register at end = "
	          << std::ranges::max(registers | std::views::values) << '\n';

	std::cout << "max register ever = " << max_value << '\n';
}
