//
// Advent of Code 2017, day 19, part one and two
//

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

auto read_diagram()
{
	std::vector<std::string> diagram;

	std::string::size_type max_width = 0;

	for (std::string line; std::getline(std::cin, line); ) {
		line = ' ' + line + ' ';

		max_width = std::max(max_width, line.size());

		diagram.push_back(std::move(line));
	}

	for (auto &line : diagram) {
		line.resize(max_width, ' ');
	}

	diagram.emplace_back(max_width, ' ');

	return diagram;
}

int main()
{
	auto diagram = read_diagram();

	int x = diagram.front().find('|');
	int y = 0;
	int dx = 0;
	int dy = 1;

	std::string letters;

	int num_steps = 0;

	for (;;) {
		if (char ch = diagram[y][x]; std::isupper(ch)) {
			letters += ch;
		}
		else if (ch == ' ') {
			break;
		}
		else if (ch == '+') {
			// Rotate {dx, dy} 90 degrees clockwise (y flipped)
			int right_dx = -dy;
			int right_dy = dx;

			// Rotate {dx, dy} 90 degrees anti-clockwise (y flipped)
			int left_dx = dy;
			int left_dy = -dx;

			if (diagram[y + right_dy][x + right_dx] != ' ') {
				dx = right_dx;
				dy = right_dy;
			}
			else if (diagram[y + left_dy][x + left_dx] != ' ') {
				dx = left_dx;
				dy = left_dy;
			}
			else {
				std::cerr << "dead end";
				exit(1);
			}
		}

		x += dx;
		y += dy;

		++num_steps;
	}

	std::cout << letters << ' ' << num_steps << '\n';
}
