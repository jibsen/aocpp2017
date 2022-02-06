//
// Advent of Code 2017, day 9, part two
//

#include <iostream>
#include <string>
#include <string_view>

int garbage_count(std::string_view sv)
{
	enum class State { normal, garbage, escaped };

	State state = State::normal;
	int num_garbage = 0;

	for (auto ch : sv) {
		switch (state) {
		case State::normal:
			switch (ch) {
			case '<':
				state = State::garbage;
				break;
			default:
				break;
			}
			break;
		case State::garbage:
			switch (ch) {
			case '!':
				state = State::escaped;
				break;
			case '>':
				state = State::normal;
				break;
			default:
				++num_garbage;
				break;
			}
			break;
		case State::escaped:
			state = State::garbage;
			break;
		}
	}

	return num_garbage;
}

int main()
{
	std::string stream;

	std::cin >> stream;

	std::cout << garbage_count(stream) << '\n';
}
