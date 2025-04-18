#pragma once
#include "Expr.h"
#include "Error.h"
#include "Stmt.h"
#include "Environment.h"
#include "LoxCallable.h"
#include "LoxFunction.h"
#include "LoxClass.h"

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
class Interpreter : public VisitorExpr, public VisitorStmt, public std::enable_shared_from_this<Interpreter>
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
	std::shared_ptr<Object> visitGetExpr(const Get& expr) override;
	std::shared_ptr<Object> visitSetExpr(const Set& expr) override;
	std::shared_ptr<Object> visitThisExpr(const This& expr) override;
	std::shared_ptr<Object> visitSuperExpr(const Super& expr) override;

	void visitExpressionStmt(std::shared_ptr<ExpressionStmt> stmt) override;
	void visitWhileStmt(std::shared_ptr<WhileStmt> stmt)  override;
	void visitIfStmt(std::shared_ptr<IfStmt> stmt) override;
	void visitPrintStmt(std::shared_ptr<PrintStmt> stmt) override;
	void visitVarStmt(std::shared_ptr<VarStmt> stmt) override;
	void visitClassStmt(std::shared_ptr<ClassStmt> stmt)override;
	void visitBlock(std::shared_ptr<Block> stmt) override;
	void visitFunctionStmt(std::shared_ptr<FunctionStmt> stmt) override;
	void visitReturnStmt(std::shared_ptr<ReturnStmt> stmt) override;

public:
	std::shared_ptr<Environment> globals;
	std::map<std::shared_ptr<Expr>, int> locals;
	void executeBlock(const std::shared_ptr<std::vector<std::shared_ptr<Stmt>>>& statements, std::shared_ptr<Environment> environment);
	void interpret(std::vector<std::shared_ptr<Stmt>> statements );
	void resolve(const std::shared_ptr<Expr> expr, int depth);
	Interpreter();

};

