#pragma once
#include "Expr.h"
#include "Error.h"
#include "Stmt.h"
#include "Environment.h"
#include "LoxCallable.h"
#include "LoxFunction.h"

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
class Interpreter : public VisitorExpr, public VisitorStmt
{
private:


	std::shared_ptr<Environment> environment; 


	std::shared_ptr<Object> evaluate(const std::shared_ptr<Expr>& expr);
	bool isTruthy(const std::shared_ptr<Object>& object);
	bool isEqual(const std::shared_ptr<Object>& left, const std::shared_ptr<Object>& right);
	void checkNumberOperand(const Token& op, const std::shared_ptr<Object>& operand);
	void checkNumberOperands(const Token& op, const std::shared_ptr<Object>& left, const std::shared_ptr<Object>& right);
	void execute(const std::shared_ptr<Stmt>& stmt);
	std::shared_ptr<Object> lookUpVariable(const Token& name, const std::shared_ptr<Expr>& expr);

	std::string stringify(const std::shared_ptr<Object>& object);

	std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) override;
	std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) override;
	std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) override;
	std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) override;
	std::shared_ptr<Object> visitVariableExpr(const Variable& expr) override;
	std::shared_ptr<Object> visitAssignExpr(const Assign& expr) override;
	std::shared_ptr<Object> visitLogicalExpr(const Logical& expr) override;
	std::shared_ptr<Object> visitCallExpr(const Call& expr) override;
	
	void visitBlock(const Block& stmt) override;	
	void visitExpressionStmt(const ExpressionStmt& stmt) override;
	void visitIfStmt(const IfStmt& stmt) override;
	void visitPrintStmt(const PrintStmt& stmt) override;
	void visitVarStmt(const VarStmt& stmt) override;
	void visitWhileStmt(const WhileStmt& stmt) override;
	void visitFunctionStmt(const FunctionStmt& stmt) override;
	void visitReturnStmt(const ReturnStmt& stmt) override;

public:
	std::shared_ptr<Environment> globals;
	std::map<std::shared_ptr<Expr>, int> locals;
	void executeBlock(const std::shared_ptr<std::vector<std::shared_ptr<Stmt>>>& statements, std::shared_ptr<Environment> environment);
	void interpret(std::vector<std::shared_ptr<Stmt>> statements );
	void resolve(const std::shared_ptr<Expr> expr, int depth);
	Interpreter();

};

