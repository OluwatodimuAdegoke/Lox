#pragma once

#include <vector>
#include <memory>
#include "Token.h"
#include "Object.h"
#include "Visitor.h"


class Expr {
public:
    virtual ~Expr() = default;
    virtual std::shared_ptr<Object> accept(Visitor& visitor) = 0;
};


class Binary : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitBinaryExpr(*this);
    }
};

class Grouping : public Expr {
public:
    std::shared_ptr<Expr> expression;

    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

class Literal : public Expr {
public:
    std::shared_ptr<Object> value;

    Literal(std::shared_ptr<Object> value) : value(value) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitLiteralExpr(*this);
    }
};

class Unary : public Expr {
public:
    Token op;
    std::shared_ptr<Expr> right;

    Unary(Token operators, std::shared_ptr<Expr> right) : op(op), right(right) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};