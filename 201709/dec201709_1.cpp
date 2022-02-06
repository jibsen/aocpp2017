//
// Advent of Code 2017, day 9, part one
//

#include <iostream>
#include <string>
#include <string_view>

int total_score(std::string_view sv)
{
	enum class State { normal, garbage, escaped };

	State state = State::normal;
	int nesting = 0;
	int score = 0;

	for (auto ch : sv) {
		switch (state) {
		case State::normal:
			switch (ch) {
			case '{':
				++nesting;
				break;
			case '}':
				score += nesting;
				--nesting;
				break;
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
				break;
			}
			break;
		case State::escaped:
			state = State::garbage;
			break;
		}
	}

	return score;
}

int main()
{
	std::string stream;

	std::cin >> stream;

	std::cout << total_score(stream) << '\n';
}
