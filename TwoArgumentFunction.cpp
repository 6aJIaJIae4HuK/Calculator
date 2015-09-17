#include <math.h>
#include <exception>
#include "TwoArgumentFunction.h"

TwoArgumentFunction::TwoArgumentFunction(TwoArgumentFunctionType functionType): functionType_(functionType) {

}

Operand TwoArgumentFunction::calculate(const Operand& op1, const Operand& op2) const {
	double res = 0.0;
	switch (functionType_) {
	case TwoArgumentFunctionType::kLog:
		if (op1.getValue() <= 0.0 || op1.getValue() == 1.0 || op2.getValue() <= 0.0)
			throw std::exception("Invalid arguments for log!!!");
		res = log(op2.getValue()) / log(op1.getValue());
		break;
	default:
		throw std::exception("Unknown function!!!");
	}
	return Operand(res);
}

Lexeme* TwoArgumentFunction::getCopy() {
	return new TwoArgumentFunction(functionType_);
}

LexemeType TwoArgumentFunction::getLexemeType() {
	return LexemeType::kTwoArgumentFunctionLexeme;
}