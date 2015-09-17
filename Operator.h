#ifndef CALCULATOR_OPERATOR_H_
#define CALCULATOR_OPERATOR_H_

#include "Lexeme.h"

class Operator : public Lexeme {
public:
	virtual int getPriority() = 0;
};

#endif