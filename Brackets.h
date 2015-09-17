#ifndef CALCULATOR_BRACKETS_H_
#define CALCULATOR_BRACKETS_H_

#include "Lexeme.h"

class OpenBracket : public Lexeme {
public:
	LexemeType getLexemeType();
	Lexeme* getCopy();
};

class CloseBracket : public Lexeme {
public:
	LexemeType getLexemeType();
	Lexeme* getCopy();
};

#endif