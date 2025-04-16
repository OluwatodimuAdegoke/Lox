#pragma once

#include <vector>
#include <memory>
#include "Token.h"
#include "Object.h"
#include "Visitor.h"
#include <cassert>

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
        return visitor.visitAssignExpr(*this);
    }
};

class Binary : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitBinaryExpr(*this);
    }
};

class Call : public Expr {
public:
    std::shared_ptr<Expr> callee;
    Token paren;
    std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments;

    Call(std::shared_ptr<Expr> callee, Token paren, std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments) : callee(callee), paren(paren), arguments(arguments) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitCallExpr(*this);
    }
};

class Get : public Expr {
public:
    std::shared_ptr<Expr> object;
    Token name;

    Get(std::shared_ptr<Expr> object, Token name) : object(object), name(name) {};

	std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitGetExpr(*this);
	}
};

class Set : public Expr {
public:
	std::shared_ptr<Expr> object;
	Token name;
	std::shared_ptr<Expr> value;
	Set(std::shared_ptr<Expr> object, Token name, std::shared_ptr<Expr> value) : object(object), name(name), value(value) {}
	std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitSetExpr(*this);
	}
};

class Super : public Expr {
public:
    Token keyword;
    Token method;
    Super(Token keyword, Token method) : keyword(keyword), method(method) {};
    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
        return visitor.visitSuperExpr(*this);
    }
};

class This : public Expr {
public:
    Token keyword;
    This(Token keyword) : keyword(keyword) {

    };

	std::shared_ptr<Object> accept(VisitorExpr& visitor) override {

		return visitor.visitThisExpr(*this);

	}
};

class Grouping : public Expr {
public:
    std::shared_ptr<Expr> expression;

    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitGroupingExpr(*this);
        //return visitor.visitGroupingExpr(*std::static_pointer_cast<Grouping>(shared_from_this()));
    }
};

class Literal : public Expr {
public:
    std::shared_ptr<Object> value;

    Literal(std::shared_ptr<Object> value) : value(value) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitLiteralExpr(*this);
    }
};

class Logical : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitLogicalExpr(*this);
    }
};

class Unary : public Expr {
public:
    Token op;
    std::shared_ptr<Expr> right;

    Unary(Token op, std::shared_ptr<Expr> right) : op(op), right(right) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitUnaryExpr(*this);
    }
};

class Variable : public Expr {
public:
    Token name;

    Variable(Token name) : name(name) {}

    std::shared_ptr<Object> accept(VisitorExpr& visitor) override {
		return visitor.visitVariableExpr(*this);
    }
};
