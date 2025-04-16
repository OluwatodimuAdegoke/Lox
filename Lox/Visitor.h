#pragma once
#include <memory>
#include "Object.h"

class Assign;
class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;
class Logical;
class Call;
class Get;
class Set;
class This;
class Super;

class ExpressionStmt;
class WhileStmt;
class PrintStmt;
class VarStmt;
class ClassStmt;
class IfStmt;
class Block;
class FunctionStmt;
class ReturnStmt;


/*
* Visitor abstract class that contains the functions to visit the different expressions
* 
* Functions:
* visitBinaryExpr: Function to visit the binary expression
* visitGroupingExpr: Function to visit the grouping expression
* visitLiteralExpr: Function to visit the literal expression
* visitUnaryExpr: Function to visit the unary expression
*/

class VisitorExpr {
public:
    virtual std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) = 0;
	virtual std::shared_ptr<Object> visitCallExpr(const Call& expr) = 0;
    virtual std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) = 0;
    virtual std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) = 0;
    virtual std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) = 0;
    virtual std::shared_ptr<Object> visitVariableExpr(const Variable& expr) = 0;
    virtual std::shared_ptr<Object> visitAssignExpr(const Assign& expr) = 0;
	virtual std::shared_ptr<Object> visitLogicalExpr(const Logical& expr) = 0;
	virtual std::shared_ptr<Object> visitGetExpr(const Get& expr) = 0;
	virtual std::shared_ptr<Object> visitSetExpr(const Set& expr) = 0;
	virtual std::shared_ptr<Object> visitThisExpr(const This& expr) = 0;
	virtual std::shared_ptr<Object> visitSuperExpr(const Super& expr) = 0;
    virtual ~VisitorExpr() = default;
};

class VisitorStmt {
public:

	virtual void visitExpressionStmt(std::shared_ptr<ExpressionStmt> stmt) = 0;
	virtual void visitWhileStmt(std::shared_ptr<WhileStmt> stmt) = 0;
	virtual void visitIfStmt(std::shared_ptr<IfStmt> stmt) = 0;
	virtual void visitPrintStmt(std::shared_ptr<PrintStmt> stmt) = 0;
	virtual void visitVarStmt(std::shared_ptr<VarStmt> stmt) = 0;
	virtual void visitClassStmt(std::shared_ptr<ClassStmt> stmt) = 0;
	virtual void visitBlock(std::shared_ptr<Block> stmt) = 0;
	virtual void visitFunctionStmt(std::shared_ptr<FunctionStmt> stmt) = 0;
	virtual void visitReturnStmt(std::shared_ptr<ReturnStmt> stmt) = 0;



 //   virtual void visitExpressionStmt(const ExpressionStmt& stmt) = 0;
	//virtual void visitWhileStmt(const WhileStmt& stmt) = 0;
	//virtual void visitIfStmt(const IfStmt& stmt) = 0;
 //   virtual void visitPrintStmt(const PrintStmt& stmt) = 0;
 //   virtual void visitVarStmt(const VarStmt& stmt) = 0; 
	//virtual void visitClassStmt(const ClassStmt& stmt) = 0;
	//virtual void visitBlock(const Block& stmt) = 0;
	//virtual void visitFunctionStmt(const FunctionStmt& stmt) = 0;
	//virtual void visitReturnStmt(const ReturnStmt& stmt) = 0;
    virtual ~VisitorStmt() = default;
};