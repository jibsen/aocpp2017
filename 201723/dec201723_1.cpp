//
// Advent of Code 2017, day 23, part one
//

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
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
	set, sub, mul, jnz
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
		{ "set", Opcode::set }, { "sub", Opcode::sub },
		{ "mul", Opcode::mul }, { "jnz", Opcode::jnz }
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
		case Opcode::set:
		case Opcode::sub:
		case Opcode::mul:
		case Opcode::jnz:
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

int main()
{
	auto program = read_program();

	Registers regs = {};

	long long mul_instructions_invoked = 0;

	for (long long ip = 0; ip >= 0 && ip < std::ssize(program); ++ip) {
		switch (program[ip].opcode) {
		case Opcode::set:
			regs[std::get<char>(program[ip].arg1)] = get_value_of(program[ip].arg2, regs);
			break;
		case Opcode::sub:
			regs[std::get<char>(program[ip].arg1)] -= get_value_of(program[ip].arg2, regs);
			break;
		case Opcode::mul:
			regs[std::get<char>(program[ip].arg1)] *= get_value_of(program[ip].arg2, regs);
			++mul_instructions_invoked;
			break;
		case Opcode::jnz:
			if (get_value_of(program[ip].arg1, regs) != 0) {
				ip += get_value_of(program[ip].arg2, regs) - 1;
			}
			break;
		}
	}

	std::cout << mul_instructions_invoked << '\n';
}
