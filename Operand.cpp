#include "Operand.h"

Operand::Operand(double value) : value_(value) {

}

LexemeType Operand::getLexemeType() {
	return LexemeType::kOperandLexeme;
}

Lexeme* Operand::getCopy() {
	return new Operand(value_);
}

double Operand::getValue() const {
	return value_;
}