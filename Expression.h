#ifndef CALCULATOR_EXPRESSION_H_
#define CALCULATOR_EXPRESSION_H_

#include <string>
#include <vector>
#include <stack>
#include "Lexeme.h"

class Expression {
public:
	explicit Expression(std::string str);
	double calculateExpression();
	~Expression();
private:
	void clear();
	void convertToLexems();
	void convertToReverse();
	void updatePrevLexeme();
	std::string expression_;
	std::vector<Lexeme*> lexems_;
	std::vector<Lexeme*> polishExpression_;
	std::stack<Lexeme*> temporaryStack_;
	Lexeme* prevLexeme_;
};

#endif