#include <exception>
#include <iterator>
#include "Brackets.h"
#include "Comma.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "OneArgumentFunction.h"
#include "TwoArgumentFunction.h"
#include "Expression.h"
#include "ReversePolishExpression.h"

Expression::Expression(std::string str) : expression_(str) {
	
}

void Expression::clear() {
	for (auto it = lexems_.begin(); it != lexems_.end(); it++) {
		delete *it;
	}

	for (auto it = polishExpression_.begin(); it != polishExpression_.end(); it++) {
		delete *it;
	}

	while (!temporaryStack_.empty()) {
		delete temporaryStack_.top();
		temporaryStack_.pop();
	}

	if (prevLexeme_ != NULL) {
		delete prevLexeme_;
	}
}

void Expression::updatePrevLexeme() {
	if (prevLexeme_ != NULL)
	{
		delete prevLexeme_;
		prevLexeme_ = NULL;
	}
	if (!lexems_.empty())
		prevLexeme_ = lexems_.back()->getCopy();
}

void Expression::convertToLexems() {
	clear();
	auto it = expression_.begin();
	while (it != expression_.end()) {
		if (isdigit(*it)) {
			auto tmp = it;
			while (it != expression_.end() && (isdigit(*it) || *it == '.'))
				it++;
			try {
				double d = std::stod(std::string(tmp, it));
				lexems_.push_back(new Operand(d));
				updatePrevLexeme();
			}
			catch (std::exception e) {
				throw e;
			}
		}
		else
		if (*it == '(') {
			lexems_.push_back(new OpenBracket());
			updatePrevLexeme();
			it++;
		}
		else
		if (*it == ')') {
			lexems_.push_back(new CloseBracket());
			updatePrevLexeme();
			it++;
		}
		else
		if (*it == '+') {
			if (it == expression_.begin() || 
				prevLexeme_->getLexemeType() == LexemeType::kOpenBracketLexeme ||
				dynamic_cast<Operator*>(prevLexeme_) != NULL)
				lexems_.push_back(new UnaryOperator(UnaryOperatorType::kUnaryPlus));
			else
				lexems_.push_back(new BinaryOperator(BinaryOperatorType::kSumOperator));
			updatePrevLexeme();
			it++;
		}
		else
		if (*it == '-') {
			if (it == expression_.begin() ||
				prevLexeme_->getLexemeType() == LexemeType::kOpenBracketLexeme ||
				dynamic_cast<Operator*>(prevLexeme_) != NULL)
				lexems_.push_back(new UnaryOperator(UnaryOperatorType::kUnaryMinus));
			else
				lexems_.push_back(new BinaryOperator(BinaryOperatorType::kSubOperator));
			it++;
			updatePrevLexeme();
		}
		else
		if (*it == '*') {
			lexems_.push_back(new BinaryOperator(BinaryOperatorType::kMulOperator));
			updatePrevLexeme();
			it++;
		}
		else
		if (*it == '/') {
			lexems_.push_back(new BinaryOperator(BinaryOperatorType::kDivOperator));
			updatePrevLexeme();
			it++;
		}
		else
		if (*it == ',') {
			lexems_.push_back(new Comma());
			updatePrevLexeme();
			it++;
		}
		else
		if (*it == ' ') {
			it++;
		}
		else
		if (expression_.find("log", std::distance(expression_.begin(), it)) == std::distance(expression_.begin(), it)) {
			lexems_.push_back(new TwoArgumentFunction(TwoArgumentFunctionType::kLog));
			updatePrevLexeme();
			it += 3;
		}
		else
		if(expression_.find("sqrt", std::distance(expression_.begin(), it)) == std::distance(expression_.begin(), it)) {
			lexems_.push_back(new OneArgumentFunction(OneArgumentFunctionType::kSqrt));
			updatePrevLexeme();
			it += 4;
		}
		else
			throw std::exception("Unknown symbol!!!");
	}
}

void Expression::convertToReverse() {
	bool correct = true;
	for (auto it = lexems_.begin(); it != lexems_.end(); it++) {
		switch ((*it)->getLexemeType()) {
		case LexemeType::kOperandLexeme: 
			polishExpression_.push_back((*it)->getCopy());
			break;
		case LexemeType::kOneArgumentFunctionLexeme:
		case LexemeType::kTwoArgumentFunctionLexeme:
		case LexemeType::kOpenBracketLexeme:
			temporaryStack_.push((*it)->getCopy());
			break;
		case LexemeType::kCloseBracketLexeme:
			correct = false;
			while (!temporaryStack_.empty()) {
				if (temporaryStack_.top()->getLexemeType() == LexemeType::kOpenBracketLexeme) {
					delete temporaryStack_.top();
					temporaryStack_.pop();
					if (!temporaryStack_.empty() &&
						(temporaryStack_.top()->getLexemeType() == LexemeType::kOneArgumentFunctionLexeme ||
						 temporaryStack_.top()->getLexemeType() == LexemeType::kTwoArgumentFunctionLexeme)) {
						polishExpression_.push_back(temporaryStack_.top()->getCopy());
						delete temporaryStack_.top();
						temporaryStack_.pop();
					}
					correct = true;
					break;
				}
				polishExpression_.push_back(temporaryStack_.top()->getCopy());
				delete temporaryStack_.top();
				temporaryStack_.pop();
			}
			if (!correct)
				throw std::exception("Invalid brackets!!!");
			break;
		case LexemeType::kCommaLexeme:
			correct = false;
			while (!temporaryStack_.empty()) {
				if (temporaryStack_.top()->getLexemeType() == LexemeType::kOpenBracketLexeme) {
					correct = true;
					break;
				}
				polishExpression_.push_back(temporaryStack_.top()->getCopy());
				delete temporaryStack_.top();
				temporaryStack_.pop();
			}
			if (!correct)
				throw std::exception("Invalid brackets!!!");
			break;
		case LexemeType::kUnaryOperatorLexeme:
			while (!temporaryStack_.empty() && dynamic_cast<Operator*>(temporaryStack_.top()) != NULL &&
				dynamic_cast<Operator*>(*it)->getPriority() <
				dynamic_cast<Operator*>(temporaryStack_.top())->getPriority()) {

				polishExpression_.push_back(temporaryStack_.top()->getCopy());
				delete temporaryStack_.top();
				temporaryStack_.pop();
			}
			temporaryStack_.push((*it)->getCopy());
			break;
		case LexemeType::kBinaryOperatorLexeme:
			while (!temporaryStack_.empty() && dynamic_cast<Operator*>(temporaryStack_.top()) != NULL &&
				dynamic_cast<Operator*>(*it)->getPriority() <=
				dynamic_cast<Operator*>(temporaryStack_.top())->getPriority()) {

				polishExpression_.push_back(temporaryStack_.top()->getCopy());
				delete temporaryStack_.top();
				temporaryStack_.pop();
			}
			temporaryStack_.push((*it)->getCopy());
			break;
		}
	}
	while (!temporaryStack_.empty()) {
		if (temporaryStack_.top()->getLexemeType() != LexemeType::kBinaryOperatorLexeme &&
			temporaryStack_.top()->getLexemeType() != LexemeType::kUnaryOperatorLexeme)
			throw std::exception("Invalid Brackets!!!");
		polishExpression_.push_back(temporaryStack_.top()->getCopy());
		delete temporaryStack_.top();
		temporaryStack_.pop();
	}
}

double Expression::calculateExpression() {
	double res = 0.0;
	try {
		convertToLexems();
		convertToReverse();
		ReversePolishExpression polishExpression(polishExpression_);
		res = polishExpression.calculateExpression();
	}
	catch (std::exception e) {
		throw e;
	}
	return res;
}

Expression::~Expression() {
	clear();
}