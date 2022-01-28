//
// Advent of Code 2017, day 2, part two
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

int main()
{
	long checksum = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream is(line);

		std::vector<long> values(std::istream_iterator<long>{is},
		                         std::istream_iterator<long>{});

		for (std::size_t j = 1; j < values.size(); ++j) {
			for (std::size_t i = 0; i != j; ++i) {
				auto [min, max] = std::minmax(values[i], values[j]);

				if (max % min == 0) {
					checksum += max / min;
				}
			}
		}
	}

	std::cout << checksum << '\n';
}
