//
// Advent of Code 2017, day 18, part two
//

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

// Helper type for visitors
template<typename... Ts>
struct Visitor : Ts... {
	using Ts::operator()...;
};

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

enum class Opcode {
	snd, set, add, mul, mod, rcv, jgz
};

using Value = std::variant<char, long long>;

struct Instruction {
	Opcode opcode;
	Value arg1;
	Value arg2;
};

using Registers = std::array<long long, 256>;

Opcode get_opcode(std::string_view sv)
{
	static const std::unordered_map<std::string_view, Opcode> lookup = {
		{ "snd", Opcode::snd }, { "set", Opcode::set },
		{ "add", Opcode::add }, { "mul", Opcode::mul },
		{ "mod", Opcode::mod }, { "rcv", Opcode::rcv },
		{ "jgz", Opcode::jgz }
	};

	return lookup.at(sv);
}

Value get_argument(std::string_view sv)
{
	if (std::islower(sv[0])) {
		return sv[0];
	}
	else {
		return std::stoll(std::string(sv));
	}
}

auto read_program()
{
	std::vector<Instruction> program;

	for (std::string line; std::getline(std::cin, line); ) {
		auto parts = split_ws(line);

		Instruction instruction;

		instruction.opcode = get_opcode(parts.at(0));

		switch (instruction.opcode) {
		case Opcode::snd:
		case Opcode::rcv:
			if (parts.size() != 2) {
				std::cerr << "wrong number of arguments\n";
				exit(1);
			}
			instruction.arg1 = get_argument(parts.at(1));
			break;
		case Opcode::set:
		case Opcode::add:
		case Opcode::mul:
		case Opcode::mod:
		case Opcode::jgz:
			if (parts.size() != 3) {
				std::cerr << "wrong number of arguments\n";
				exit(1);
			}
			instruction.arg1 = get_argument(parts.at(1));
			instruction.arg2 = get_argument(parts.at(2));
			break;
		default:
			std::cerr << "invalid opcode\n";
			exit(1);
			break;
		}

		program.push_back(std::move(instruction));
	}

	return program;
}

long long get_value_of(Value arg, const Registers &regs)
{
	return std::visit(Visitor {
		[&regs](char ch) { return regs[ch]; },
		[](long long v) { return v; }
	}, arg);
}

struct Computer {
	std::vector<Instruction> program;
	Registers regs = {};
	long long ip = 0;
	bool idle = false;
	bool done = false;
	int num_sent = 0;
	std::queue<long long> out_queue;
	std::queue<long long> in_queue;

	Computer(std::vector<Instruction> program, int id)
		: program(std::move(program))
	{
		regs['p'] = id;
	}

	void step();
};

void Computer::step()
{
	switch (program[ip].opcode) {
	case Opcode::snd:
		out_queue.push(get_value_of(program[ip].arg1, regs));
		++num_sent;
		break;
	case Opcode::set:
		regs[std::get<char>(program[ip].arg1)] = get_value_of(program[ip].arg2, regs);
		break;
	case Opcode::add:
		regs[std::get<char>(program[ip].arg1)] += get_value_of(program[ip].arg2, regs);
		break;
	case Opcode::mul:
		regs[std::get<char>(program[ip].arg1)] *= get_value_of(program[ip].arg2, regs);
		break;
	case Opcode::mod:
		regs[std::get<char>(program[ip].arg1)] %= get_value_of(program[ip].arg2, regs);
		break;
	case Opcode::rcv:
		if (in_queue.empty()) {
			idle = true;
			return;
		}
		idle = false;
		regs[std::get<char>(program[ip].arg1)] = in_queue.front();
		in_queue.pop();
		break;
	case Opcode::jgz:
		if (get_value_of(program[ip].arg1, regs) > 0) {
			ip += get_value_of(program[ip].arg2, regs) - 1;
		}
		break;
	}

	++ip;

	if (ip < 0 || ip >= std::ssize(program)) {
		done = true;
	}
}

int main()
{
	auto program = read_program();

	Computer cpu0(program, 0);
	Computer cpu1(program, 1);

	while (!cpu0.done || !cpu1.done) {
		cpu0.step();

		while (!cpu0.out_queue.empty()) {
			cpu1.in_queue.push(cpu0.out_queue.front());
			cpu0.out_queue.pop();
		}

		cpu1.step();

		while (!cpu1.out_queue.empty()) {
			cpu0.in_queue.push(cpu1.out_queue.front());
			cpu1.out_queue.pop();
		}

		if (cpu0.idle && cpu1.idle) {
			break;
		}
	}

	std::cout << cpu1.num_sent << '\n';
}
