#ifndef CALCULATOR_BINARY_OPERATOR_H_
#define CALCULATOR_BINARY_OPERATOR_H_

#include "Operator.h"
#include "Operand.h"

enum BinaryOperatorType {
	kSumOperator,
	kSubOperator,
	kMulOperator,
	kDivOperator
};

class BinaryOperator : public Operator {
public:
	explicit BinaryOperator(BinaryOperatorType operatorType);
	Operand calculate(const Operand& op1, const Operand& op2) const;
	int getPriority();
	LexemeType getLexemeType();
	Lexeme* getCopy();
private:
	BinaryOperatorType operatorType_;
};

#endif