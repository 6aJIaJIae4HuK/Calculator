#ifndef CALCULATOR_TWO_ARGUMENT_FUNCTION_H_
#define CALCULATOR_TWO_ARGUMENT_FUNCTION_H_

#include "Lexeme.h"
#include "Operand.h"

enum TwoArgumentFunctionType {
	kLog
};

class TwoArgumentFunction : public Lexeme {
public:
	explicit TwoArgumentFunction(TwoArgumentFunctionType type);
	Lexeme* getCopy();
	LexemeType getLexemeType();
	Operand calculate(const Operand& op1, const Operand& op2) const;
private:
	TwoArgumentFunctionType functionType_;
};

#endif