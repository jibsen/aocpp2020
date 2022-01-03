//
// Advent of Code 2020, day 8, part two
//

// Since there aren't that many nop/jmp instructions, we can afford to
// try replacing each in order and see if the program terminates.

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

enum class Opcode { acc, jmp, nop };

auto read_program()
{
	static const std::unordered_map<std::string_view, Opcode> lookup = {
		{ "acc", Opcode::acc }, { "jmp", Opcode::jmp }, { "nop", Opcode::nop }
	};

	std::vector<std::pair<Opcode, int>> program;

	std::string opcode;
	int offs = 0;

	while (std::cin >> opcode >> offs) {
		program.emplace_back(lookup.at(opcode), offs);
	}

	return program;
}

std::optional<long> emulate_program(const std::vector<std::pair<Opcode, int>> &program)
{
	std::vector<bool> visited(program.size(), false);

	long acc = 0;
	std::size_t ip = 0;

	for (;;) {
		if (visited[ip]) {
			return {};
		}

		visited[ip] = true;

		if (ip == program.size()) {
			return acc;
		}

		auto [op, offs] = program[ip++];

		switch (op) {
		case Opcode::acc:
			acc += offs;
			break;
		case Opcode::jmp:
			ip += offs - 1;
			break;
		case Opcode::nop:
			break;
		}
	}
}

int main()
{
	auto program = read_program();

	for (auto &[op, offs] : program) {
		switch (op) {
		case Opcode::acc:
			continue;
		case Opcode::jmp:
			op = Opcode::nop;
			break;
		case Opcode::nop:
			op = Opcode::jmp;
			break;
		}

		if (auto res = emulate_program(program)) {
			std::cout << *res << '\n';
			break;
		}

		switch (op) {
		case Opcode::acc:
			continue;
		case Opcode::jmp:
			op = Opcode::nop;
			break;
		case Opcode::nop:
			op = Opcode::jmp;
			break;
		}
	}
}
