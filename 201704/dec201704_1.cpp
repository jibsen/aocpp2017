//
// Advent of Code 2017, day 4, part one
//

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

auto split_ws(std::string_view sv)
{
	const auto is_ws = [](unsigned char ch) { return std::isspace(ch); };

	std::vector<std::string_view> res;

	auto pos = sv.begin();

	for (;;) {
		pos = std::find_if_not(pos, sv.end(), is_ws);

		if (pos == sv.end()) {
			break;
		}

		auto start = pos;

		pos = std::find_if(pos, sv.end(), is_ws);

		res.push_back(sv.substr(start - sv.begin(), pos - start));
	}

	return res;
}

bool is_valid(std::string_view passphrase)
{
	std::unordered_set<std::string_view> seen;

	for (auto word : split_ws(passphrase)) {
		if (auto [it, success] = seen.insert(word); !success) {
			return false;
		}
	}

	return true;
}

int main()
{
	int num_valid = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		num_valid += static_cast<int>(is_valid(line));
	}

	std::cout << num_valid << '\n';
}
