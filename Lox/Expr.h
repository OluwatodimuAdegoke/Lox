#pragma once

#include <vector>
#include <memory>
#include "Token.h"
#include "Object.h"
#include "Visitor.h"

class Expr : public std::enable_shared_from_this<Expr> {
public:
    virtual ~Expr() = default;
    virtual std::shared_ptr<Object> accept(VisitorExpr& visitor) = 0;
};

class Assign : public Expr {
public:
    Token name;
    std::shared_ptr<Expr> value;

    Assign(Token name, std::shared_ptr<Expr> value) : name(name), value(value) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitAssignExpr(*std::static_pointer_cast<Assign>(shared_from_this()));
    }
};

class Binary : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitBinaryExpr(*std::static_pointer_cast<Binary>(shared_from_this()));
    }
};

class Call : public Expr {
public:
    std::shared_ptr<Expr> callee;
    Token paren;
    std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments;

    Call(std::shared_ptr<Expr> callee, Token paren, std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments) : callee(callee), paren(paren), arguments(arguments) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitCallExpr(*std::static_pointer_cast<Call>(shared_from_this()));
    }
};

class Grouping : public Expr {
public:
    std::shared_ptr<Expr> expression;

    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitGroupingExpr(*std::static_pointer_cast<Grouping>(shared_from_this()));
    }
};

class Literal : public Expr {
public:
    std::shared_ptr<Object> value;

    Literal(std::shared_ptr<Object> value) : value(value) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitLiteralExpr(*std::static_pointer_cast<Literal>(shared_from_this()));
    }
};

class Logical : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitLogicalExpr(*std::static_pointer_cast<Logical>(shared_from_this()));
    }
};

class Unary : public Expr {
public:
    Token op;
    std::shared_ptr<Expr> right;

    Unary(Token op, std::shared_ptr<Expr> right) : op(op), right(right) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitUnaryExpr(*std::static_pointer_cast<Unary>(shared_from_this()));
    }
};

class Variable : public Expr {
public:
    Token name;

    Variable(Token name) : name(name) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitVariableExpr(*std::static_pointer_cast<Variable>(shared_from_this()));
    }
};
