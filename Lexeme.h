#ifndef CALCULATOR_LEXEME_H_
#define CALCULATOR_LEXEME_H_

enum LexemeType {
	kOperandLexeme,
	kUnaryOperatorLexeme,
	kBinaryOperatorLexeme,
	kOneArgumentFunctionLexeme,
	kTwoArgumentFunctionLexeme,
	kOpenBracketLexeme,
	kCloseBracketLexeme,
	kCommaLexeme
};

class Lexeme {
public:
	virtual LexemeType getLexemeType() = 0;
	virtual Lexeme* getCopy() = 0;
};

#endif