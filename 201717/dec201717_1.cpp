//
// Advent of Code 2017, day 17, part one
//

#include <iostream>
#include <list>

int main()
{
	constexpr int delta = 316;

	std::list<int> list;

	list.push_back(0);

	int pos = 0;

	for (int i = 1; i <= 2017; ++i) {
		pos = ((pos + delta) % list.size()) + 1;

		list.insert(std::next(list.begin(), pos), i);
	}

	std::cout << *std::next(list.begin(), (pos + 1) % list.size()) << '\n';
}
