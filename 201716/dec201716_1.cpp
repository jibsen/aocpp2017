//
// Advent of Code 2017, day 16, part one
//

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

auto split(std::string_view sv, std::string_view delim)
{
	std::vector<std::string_view> res;

	std::string_view::size_type pos = 0;

	for (;;) {
		auto next_delim_pos = sv.find(delim, pos);

		res.push_back(sv.substr(pos, next_delim_pos - pos));

		if (next_delim_pos == std::string_view::npos) {
			break;
		}

		pos = next_delim_pos + delim.size();
	}

	return res;
}

void spin(std::string &s, int x)
{
	std::rotate(s.begin(), s.end() - x, s.end());
}

void exchange(std::string &s, int a, int b)
{
	std::swap(s[a], s[b]);
}

void partner(std::string &s, char a, char b)
{
	std::swap(s[s.find(a)], s[s.find(b)]);
}

int main()
{
	std::string programs(16, ' ');

	std::iota(programs.begin(), programs.end(), 'a');

	std::string line;

	std::getline(std::cin, line);

	auto directions = split(line, ",");

	for (auto d : directions) {
		switch (d[0]) {
		case 's':
			spin(programs, std::stoi(std::string(d.substr(1))));
			break;
		case 'x':
			{
				int a = std::stoi(std::string(d.substr(1, d.find('/'))));
				int b = std::stoi(std::string(d.substr(d.find('/') + 1)));
				exchange(programs, a, b);
			}
			break;
		case 'p':
			partner(programs, d[1], d[3]);
			break;
		}
	}

	std::cout << programs << '\n';
}
