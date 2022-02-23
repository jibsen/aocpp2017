//
// Advent of Code 2017, day 25, part one
//

// To avoid parsing the input file with C++, I hardcoded the state machine.

#include <algorithm>
#include <deque>
#include <iostream>

std::size_t simulate_machine()
{
	enum class State { A, B, C, D, E, F };

	State state = State::A;
	std::deque<char> memory = { '0' };
	auto cur = memory.begin();

	for (std::size_t steps = 0; steps < 12'523'873; ++steps) {
		if (cur == memory.begin()) {
			memory.push_front('0');
			cur = memory.begin() + 1;
		}

		switch (state) {
		case State::A:
			if (*cur == '0') {
				*cur = '1';
				++cur;
				state = State::B;
			}
			else {
				--cur;
				state = State::E;
			}
			break;
		case State::B:
			if (*cur == '0') {
				*cur = '1';
				++cur;
				state = State::C;
			}
			else {
				++cur;
				state = State::F;
			}
			break;
		case State::C:
			if (*cur == '0') {
				*cur = '1';
				--cur;
				state = State::D;
			}
			else {
				*cur = '0';
				++cur;
				state = State::B;
			}
			break;
		case State::D:
			if (*cur == '0') {
				*cur = '1';
				++cur;
				state = State::E;
			}
			else {
				*cur = '0';
				--cur;
				state = State::C;
			}
			break;
		case State::E:
			if (*cur == '0') {
				*cur = '1';
				--cur;
				state = State::A;
			}
			else {
				*cur = '0';
				++cur;
				state = State::D;
			}
			break;
		case State::F:
			if (*cur == '0') {
				*cur = '1';
				++cur;
				state = State::A;
			}
			else {
				++cur;
				state = State::C;
			}
			break;
		}

		if (cur == memory.end()) {
			memory.push_back('0');
			cur = memory.end() - 1;
		}
	}

	return std::ranges::count(memory, '1');
}

int main()
{
	std::cout << simulate_machine() << '\n';
}
