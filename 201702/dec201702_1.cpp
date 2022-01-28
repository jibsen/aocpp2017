//
// Advent of Code 2017, day 2, part one
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

		auto [min, max] = std::ranges::minmax(values);

		checksum += max - min;

	}

	std::cout << checksum << '\n';
}
