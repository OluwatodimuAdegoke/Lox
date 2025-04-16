// Resolver.h
#pragma once
#include "Interpreter.h"

enum class FunctionType {
    NONE,
    FUNCTION,
	INITIALIZER,
	METHOD,
};

enum class ClassType {
	NONE,
	CLASS,
	SUBCLASS,
};

class Resolver : public VisitorExpr, VisitorStmt {
private:
    std::shared_ptr<Interpreter> interpreter;
    std::shared_ptr<std::vector<std::map<std::string, bool>>> scopes = std::make_shared<std::vector<std::map<std::string, bool>>>();
    void beginScope();
    void endScope();
    void declare(const Token& name);
    void define(const Token& name);
    void resolveLocal(std::shared_ptr<const Expr> expr, const Token& name);

    void resolveFunction(const FunctionStmt& stmt, FunctionType type);

public:
    Resolver(std::shared_ptr<Interpreter> interpreter) {
		this->interpreter = interpreter;
    };
    void resolve(std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> statements);
    void resolve(std::shared_ptr<Stmt> stmt);
    void resolve(std::shared_ptr<Expr> expr);

private:
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

    FunctionType currentFunction = FunctionType::NONE;
	ClassType currentClass = ClassType::NONE;
};