#pragma once

#include <vector>
#include <memory>
#include "Token.h"
#include "Object.h"
#include "Visitor.h"

/*
* Expr abstract class that contains the functions to accept the visitor
* 
* Function:
* accept: Function to accept the visitor using the visitor pattern
*/

class Expr {
public:
    virtual ~Expr() = default;
    virtual std::shared_ptr<Object> accept(Visitor& visitor) = 0;
};


/*
* Binary class that contains the functions to create a binary expression
* 
* Variables:
* left: is a shared pointer to an Expr that contains the left expression
* op: is a Token that contains the operator
* right: is a shared pointer to an Expr that contains the right expression
* 
* Functions:
* Binary: Constructor that creates a binary expression with the left, operator, and right expression
* accept: Function to accept the visitor using the visitor pattern
*/
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


/*
* Grouping class that contains the functions to create a grouping expression
* 
* Variables:
* expression: is a shared pointer to an Expr that contains the expression
* 
* Functions:
* Grouping: Constructor that creates a grouping expression with the expression
* accept: Function to accept the visitor using the visitor pattern
*/
class Grouping : public Expr {
public:
    std::shared_ptr<Expr> expression;

    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

/*
* Literal class that contains the functions to create a literal expression
* 
* Variables:
* value: is a shared pointer to an Object that contains the value
* 
* Functions:
* Literal: Constructor that creates a literal expression with the value
* accept: Function to accept the visitor using the visitor pattern
*/
class Literal : public Expr {
public:
    std::shared_ptr<Object> value;

    Literal(std::shared_ptr<Object> value) : value(value) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitLiteralExpr(*this);
    }
};

/*
* Unary class that contains the functions to create a unary expression
*   
* Variables:
* op: is a Token that contains the operator
* right: is a shared pointer to an Expr that contains the right expression
* 
* Functions:
* Unary: Constructor that creates a unary expression with the operator and right expression
* accept: Function to accept the visitor using the visitor pattern
*/

class Unary : public Expr {
public:
    Token op;
    std::shared_ptr<Expr> right;

    Unary(Token operators, std::shared_ptr<Expr> right) : op(op), right(right) {}

    std::shared_ptr<Object> accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};