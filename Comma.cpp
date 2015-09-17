#include "Comma.h"

LexemeType Comma::getLexemeType() {
	return LexemeType::kCommaLexeme;
}

Lexeme* Comma::getCopy() {
	return new Comma();
}