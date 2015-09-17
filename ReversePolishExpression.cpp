#include <exception>
#include <algorithm>
#include "Operand.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "OneArgumentFunction.h"
#include "TwoArgumentFunction.h"
#include "ReversePolishExpression.h"

ReversePolishExpression::ReversePolishExpression(std::vector<Lexeme*> lexems) : lexems_(lexems) {
	lexems_.resize(lexems.size());
	for (auto it = lexems.begin(); it != lexems.end(); it++) {
		*(lexems_.begin() + std::distance(lexems.begin(), it)) = (*it)->getCopy();
	}
}

double ReversePolishExpression::calculateExpression() {
	while (!stack_.empty()) {
		delete stack_.top();
		stack_.pop();
	}
	try {
		for (auto it = lexems_.begin(); it != lexems_.end(); it++) {
			switch ((*it)->getLexemeType()) {
			case LexemeType::kOperandLexeme:
				{
					stack_.push(new Operand(dynamic_cast<Operand*>(*it)->getValue()));
					break;
				}
			case LexemeType::kBinaryOperatorLexeme:
				{
					if (stack_.size() < 2)
						throw std::exception("Too few arguments for binary operator!!!");
					Operand op2 = *stack_.top();
					delete stack_.top();
					stack_.pop();
					Operand op1 = *stack_.top();
					delete stack_.top();
					stack_.pop();
					Operand res = dynamic_cast<BinaryOperator*>(*it)->calculate(op1, op2);
					stack_.push(new Operand(res.getValue()));
					break;
				}
			case LexemeType::kUnaryOperatorLexeme:
				{
					if (stack_.size() < 1)
						throw std::exception("Too few arguments for unary operator!!!");
					Operand op = *stack_.top();
					delete stack_.top();
					stack_.pop();
					Operand res = dynamic_cast<UnaryOperator*>(*it)->calculate(op);
					stack_.push(new Operand(res.getValue()));
					break;
				}
			case LexemeType::kOneArgumentFunctionLexeme:
				{
					if (stack_.size() < 1)
						throw std::exception("Too few arguments for unary function!!!");
					Operand op = *stack_.top();
					delete stack_.top();
					stack_.pop();
					Operand res = dynamic_cast<OneArgumentFunction*>(*it)->calculate(op);
					stack_.push(new Operand(res.getValue()));
					break;
				}
			case LexemeType::kTwoArgumentFunctionLexeme: 
				{
					if (stack_.size() < 2)
						throw std::exception("Too few arguments for binary function!!!");
					Operand op2 = *stack_.top();
					delete stack_.top();
					stack_.pop();
					Operand op1 = *stack_.top();
					delete stack_.top();
					stack_.pop();
					Operand res = dynamic_cast<TwoArgumentFunction*>(*it)->calculate(op1, op2);
					stack_.push(new Operand(res.getValue()));
					break;
				}
			}
		}

		if (stack_.size() != 1)
			throw std::exception("Missing operator or function!!!");
	}
	catch (std::exception e) {
		throw e;
	}
	return stack_.top()->getValue();
}

ReversePolishExpression::~ReversePolishExpression() {
	while (!stack_.empty()) {
		delete stack_.top();
		stack_.pop();
	}

	for (auto it = lexems_.begin(); it != lexems_.end(); it++)
		delete *it;
}