//
// Advent of Code 2020, day 8, part one
//

#include <iostream>
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


int main()
{
	auto program = read_program();

	std::vector<bool> visited(program.size(), false);

	long acc = 0;
	std::size_t ip = 0;

	for (;;) {
		if (visited[ip]) {
			std::cout << acc << '\n';
			break;
		}

		visited[ip] = true;

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
