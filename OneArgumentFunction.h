#ifndef CALCULATOR_ONE_ARGUMENT_FUNCTION_H_
#define CALCULATOR_ONE_ARGUMENT_FUNCTION_H_

#include "Lexeme.h"
#include "Operand.h"

enum OneArgumentFunctionType {
	kSqrt
};

class OneArgumentFunction : public Lexeme {
public:
	explicit OneArgumentFunction(OneArgumentFunctionType type);
	Lexeme* getCopy();
	LexemeType getLexemeType();
	Operand calculate(const Operand& op) const;
private:
	OneArgumentFunctionType functionType_;
};

#endif