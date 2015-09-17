#ifndef CALCULATOR_UNARY_OPERATOR_H_
#define CALCULATOR_UNARY_OPERATOR_H_

#include "Operator.h"
#include "Operand.h"

enum UnaryOperatorType {
	kUnaryPlus,
	kUnaryMinus
};

class UnaryOperator : public Operator {
public:
	explicit UnaryOperator(UnaryOperatorType operatorType);
	Operand calculate(const Operand& op) const;
	int getPriority();
	LexemeType getLexemeType();
	Lexeme* getCopy();
private:
	UnaryOperatorType operatorType_;
};

#endif