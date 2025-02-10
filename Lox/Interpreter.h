#pragma once
#include "Expr.h"
#include "Error.h"


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

