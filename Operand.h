#ifndef CALCULATOR_OPERAND_H_
#define CALCULATOR_OPERAND_H_

#include "Lexeme.h"

class Operand : public Lexeme {
public:
	explicit Operand(double value);
	double getValue() const;
	LexemeType getLexemeType();
	Lexeme* getCopy();
private:
	double value_;
};

#endif