#include <exception>
#include "UnaryOperator.h"

UnaryOperator::UnaryOperator(UnaryOperatorType operatorType) : operatorType_(operatorType) {

}

Operand UnaryOperator::calculate(const Operand& op) const {
	double res = 0.0;
	switch (operatorType_) {
	case UnaryOperatorType::kUnaryPlus:
		res = op.getValue();
		break;
	case UnaryOperatorType::kUnaryMinus:
		res = -op.getValue();
		break;
	default:
		throw std::exception("Unknown unary operator!!!");
	}
	return Operand(res);
}

int UnaryOperator::getPriority() {
	int res = -1;
	switch (operatorType_) {
	case UnaryOperatorType::kUnaryPlus:
	case UnaryOperatorType::kUnaryMinus:
		res = 4;
		break;
	default:
		throw std::exception("Unknown unary operator!!!");
	}
	return res;
}

LexemeType UnaryOperator::getLexemeType() {
	return LexemeType::kUnaryOperatorLexeme;
}

Lexeme* UnaryOperator::getCopy() {
	return new UnaryOperator(operatorType_);
}