#pragma once
#include "Expr.h"
#include "Error.h"

/*
* Interpreter class that contains the functions to interpret the expressions
* gotton from the parser. It inherits from the Visitor class and contains the functions
* to visit the different expressions and evaluate them to get the result.
* 
* Functions:
* evaluate: Function to evaluate the expression
* interpret: Function to interpret the expression
* visitLiteralExpr: Function to visit the literal expression
* visitGroupingExpr: Function to visit the grouping expression
* visitBinaryExpr: Function to visit the binary expression
* visitUnaryExpr: Function to visit the unary expression
* 
* Helper Functions:
* isTruthy: Function to check if the object is truthy or not
* isEqual: Function to check if the two objects are equal
* checkNumberOperand: Function to check if the operand is a number
* checkNumberOperands: Function to check if the operands are numbers
* stringify: Function to convert the object to a string
*/
class Interpreter : public Visitor
{
private:

	std::shared_ptr<Object> evaluate(const std::shared_ptr<Expr>& expr);
	bool isTruthy(const std::shared_ptr<Object>& object);
	bool isEqual(const std::shared_ptr<Object>& left, const std::shared_ptr<Object>& right);
	void checkNumberOperand(const Token& op, const std::shared_ptr<Object>& operand);
	void checkNumberOperands(const Token& op, const std::shared_ptr<Object>& left, const std::shared_ptr<Object>& right);
	
	std::string stringify(const std::shared_ptr<Object>& object);

	std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) override;
	std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) override;
	std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) override;
	std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) override;

public:
	void interpret(const std::shared_ptr<Expr>& expr);

};

