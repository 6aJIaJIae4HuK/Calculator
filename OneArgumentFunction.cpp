#include <exception>
#include <cmath>
#include "OneArgumentFunction.h"

OneArgumentFunction::OneArgumentFunction(OneArgumentFunctionType functionType) : functionType_(functionType) {

}

Operand OneArgumentFunction::calculate(const Operand& op) const {
	double res = 0.0;
	switch (functionType_) {
	case OneArgumentFunctionType::kSqrt:
		if (op.getValue() < 0.0)
			throw std::exception("Invalid arguments for sqrt!!!");
		res = sqrt(op.getValue());
		break;
	default:
		throw std::exception("Unknown function!!!");
	}
	return Operand(res);
}

Lexeme* OneArgumentFunction::getCopy() {
	return new OneArgumentFunction(functionType_);
}

LexemeType OneArgumentFunction::getLexemeType() {
	return LexemeType::kOneArgumentFunctionLexeme;
}