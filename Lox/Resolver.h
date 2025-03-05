// Resolver.h
#pragma once
#include "Interpreter.h"

enum class FunctionType {
    NONE,
    FUNCTION,
};

class Resolver : public VisitorExpr, VisitorStmt {
private:
    std::shared_ptr<Interpreter> interpreter;
    std::shared_ptr<std::vector<std::map<std::string, bool>>> scopes = std::make_shared<std::vector<std::map<std::string, bool>>>();
    void beginScope();
    void endScope();
    void declare(const Token& name);
    void define(const Token& name);
    void resolveLocal(const Expr& expr, const Token& name);
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

    void visitBlock(const Block& stmt) override;
    void visitExpressionStmt(const ExpressionStmt& stmt) override;
    void visitIfStmt(const IfStmt& stmt) override;
    void visitPrintStmt(const PrintStmt& stmt) override;
    void visitVarStmt(const VarStmt& stmt) override;
    void visitWhileStmt(const WhileStmt& stmt) override;
    void visitFunctionStmt(const FunctionStmt& stmt) override;
    void visitReturnStmt(const ReturnStmt& stmt) override;

    FunctionType currentFunction = FunctionType::NONE;
};