#ifndef CALCULATOR_REVERSE_POLISH_EXPRESSION_H_
#define CALCULATOR_REVERSE_POLISH_EXPRESSION_H_

#include <vector>
#include <stack>
#include "Lexeme.h"
#include "Operand.h"

class ReversePolishExpression {
public:
	explicit ReversePolishExpression(std::vector<Lexeme*> lexems);
	double calculateExpression();
	~ReversePolishExpression();
private:
	std::vector<Lexeme*> lexems_;
	std::stack<Operand*> stack_;
};

#endif