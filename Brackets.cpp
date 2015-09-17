#include "Brackets.h"

LexemeType OpenBracket::getLexemeType() {
	return LexemeType::kOpenBracketLexeme;
}

Lexeme* OpenBracket::getCopy() {
	return new OpenBracket();
}

LexemeType CloseBracket::getLexemeType() {
	return LexemeType::kCloseBracketLexeme;
}

Lexeme* CloseBracket::getCopy() {
	return new CloseBracket();
}