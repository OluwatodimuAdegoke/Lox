#pragma once

#include <vector>
#include <memory>
#include "Token.h"

class Visitor;
class Binary;
class Grouping;
class Literal;
class Unary;

class Expr {
public:
    virtual ~Expr() = default;
    virtual std::string accept(Visitor& visitor) = 0;
};

class Visitor {
public:
    virtual std::string visitBinaryExpr(const Binary& expr) = 0;
    virtual std::string visitGroupingExpr(const Grouping& expr) = 0;
    virtual std::string visitLiteralExpr(const Literal& expr) = 0;
    virtual std::string visitUnaryExpr(const Unary& expr) = 0;
    virtual ~Visitor() = default;
};

class Binary : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token operators;
    std::shared_ptr<Expr> right;

    Binary(std::shared_ptr<Expr> left, Token operators, std::shared_ptr<Expr> right) : left(left), operators(operators), right(right) {}

    std::string accept(Visitor& visitor) override {
        return visitor.visitBinaryExpr(*this);
    }
};

class Grouping : public Expr {
public:
    std::shared_ptr<Expr> expression;

    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

    std::string accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

class Literal : public Expr {
public:
    std::shared_ptr<Object> value;

    Literal(std::shared_ptr<Object> value) : value(value) {}

    std::string accept(Visitor& visitor) override {
        return visitor.visitLiteralExpr(*this);
    }
};

class Unary : public Expr {
public:
    Token operators;
    std::shared_ptr<Expr> right;

    Unary(Token operators, std::shared_ptr<Expr> right) : operators(operators), right(right) {}

    std::string accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};