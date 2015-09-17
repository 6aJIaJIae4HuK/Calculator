#ifndef CALCULATOR_COMMA_H_
#define CALCULATOR_COMMA_H_

#include "Lexeme.h"

class Comma : public Lexeme {
public:
	LexemeType getLexemeType();
	Lexeme* getCopy();
};

#endif