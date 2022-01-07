//
// Advent of Code 2020, day 18, part one
//

#include <format>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

enum class Token {
	plus, multiply, open_par, close_par, digit
};

auto read_expressions()
{
	std::vector<std::vector<std::pair<Token, int>>> expressions;

	for (std::string line; std::getline(std::cin, line); ) {
		std::vector<std::pair<Token, int>> expression;

		for (char ch : line) {
			switch (ch) {
			case '+':
				expression.emplace_back(Token::plus, 0);
				continue;
			case '*':
				expression.emplace_back(Token::multiply, 0);
				continue;
			case '(':
				expression.emplace_back(Token::open_par, 0);
				continue;
			case ')':
				expression.emplace_back(Token::close_par, 0);
				continue;
			}

			if (ch >= '0' && ch <= '9') {
				expression.emplace_back(Token::digit, ch - '0');
				continue;
			}
		}

		expressions.push_back(std::move(expression));
	}

	return expressions;
}

constexpr long long apply_op(Token op, long long lhs, long long rhs)
{
	switch (op) {
	case Token::plus:
		return lhs + rhs;
	case Token::multiply:
		return lhs * rhs;
	default:
		std::cerr << "apply_op unexpected operator\n";
		exit(1);
	}
}

long long evaluate_expression(const std::vector<std::pair<Token, int>> &exp)
{
	std::stack<Token> operators;
	std::stack<long long> values;

	for (auto [type, value] : exp) {
		switch (type) {
		case Token::digit:
			values.push(value);
			break;
		case Token::open_par:
			operators.push(type);
			break;
		case Token::plus:
			[[fallthrough]];
		case Token::multiply:
			while (!operators.empty() && operators.top() != Token::open_par) {
				auto op = operators.top();
				operators.pop();

				auto rhs = values.top();
				values.pop();
				auto lhs = values.top();
				values.pop();

				values.push(apply_op(op, lhs, rhs));
			}

			operators.push(type);
			break;
		case Token::close_par:
			while (operators.top() != Token::open_par) {
				auto op = operators.top();
				operators.pop();

				auto rhs = values.top();
				values.pop();
				auto lhs = values.top();
				values.pop();

				values.push(apply_op(op, lhs, rhs));
			}

			operators.pop();
			break;
		}
	}

	while (!operators.empty()) {
		auto op = operators.top();
		operators.pop();

		auto rhs = values.top();
		values.pop();
		auto lhs = values.top();
		values.pop();

		values.push(apply_op(op, lhs, rhs));
	}

	return values.top();
}

int main()
{
	auto expressions = read_expressions();

	std::cout << std::format("{} expressions read\n", expressions.size());

	auto value_view = expressions | std::views::transform(evaluate_expression) | std::views::common;

	std::cout << std::accumulate(value_view.begin(), value_view.end(), 0LL) << '\n';
}
