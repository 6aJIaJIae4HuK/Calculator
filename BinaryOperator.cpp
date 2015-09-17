#include <exception>
#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(BinaryOperatorType operatorType) : operatorType_(operatorType) {

}

Operand BinaryOperator::calculate(const Operand& op1, const Operand& op2) const {
	double res = 0.0;
	switch (operatorType_) {
	case BinaryOperatorType::kSumOperator:
		res = op1.getValue() + op2.getValue();
		break;
	case BinaryOperatorType::kSubOperator:
		res = op1.getValue() - op2.getValue();
		break;
	case BinaryOperatorType::kMulOperator:
		res = op1.getValue() * op2.getValue();
		break;
	case BinaryOperatorType::kDivOperator:
		if (op2.getValue() == 0.0)
			throw std::exception("Division by zero!!!");
		res = op1.getValue() / op2.getValue();
		break;
	default:
		throw std::exception("Unknown binary operator!!!");
	}
	return Operand(res);
}

int BinaryOperator::getPriority(){
	int res = -1;
	switch (operatorType_) {
	case BinaryOperatorType::kSumOperator:
	case BinaryOperatorType::kSubOperator:
		res = 1;
		break;
	case BinaryOperatorType::kMulOperator:
	case BinaryOperatorType::kDivOperator:
		res = 2;
		break;
	default:
		throw std::exception("Unknown binary operator!!!");
	}
	return res;
}

LexemeType BinaryOperator::getLexemeType() {
	return LexemeType::kBinaryOperatorLexeme;
}

Lexeme* BinaryOperator::getCopy() {
	return new BinaryOperator(operatorType_);
}