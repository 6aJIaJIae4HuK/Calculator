#include "Brackets.h"
#include "OneArgumentFunction.h"
#include "TwoArgumentFunction.h"
#include "BinaryOperator.h"
#include "Lexeme.h"
#include "Operand.h"
#include "UnaryOperator.h"
#include "BinaryOperator.h"
#include "ReversePolishExpression.h"
#include "Expression.h"

#include <iostream>
#include <string>

int main() {
	std::string str;
	std::getline(std::cin, str, '\n');
	try {
		Expression expr(str);
		double res = expr.calculateExpression();
		std::cout << res << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}