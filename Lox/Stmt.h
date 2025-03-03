#pragma once

#include <vector>
#include <memory>
#include "Token.h"
#include "Object.h"
#include "Visitor.h"

#include "Expr.h"
/*
* Stmt abstract class that contains the functions to accept the visitor
* 
* Function:
* accept: Function to accept the visitor using the visitor pattern
*/
class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void accept(VisitorStmt& visitor) = 0;
};

/*
* Block class that contains the functions to create a block expression
* 
* Variables:
* statements: is a shared pointer to an std::vector<std::shared_ptr<Stmt>> that contains the statements
* 
* Functions:
* Block: Constructor that creates a block expression with the statements, 
* accept: Function to accept the visitor using the visitor pattern
*/
class Block : public Stmt {
public:
    std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> statements;

    Block(std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> statements) : statements(statements) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitBlock(*this);
    }
};

/*
* ExpressionStmt class that contains the functions to create a expressionstmt expression
* 
* Variables:
* expression: is a shared pointer to an Expr that contains the expression
* 
* Functions:
* ExpressionStmt: Constructor that creates a expressionstmt expression with the expression, 
* accept: Function to accept the visitor using the visitor pattern
*/
class ExpressionStmt : public Stmt {
public:
    std::shared_ptr<Expr> expression;

    ExpressionStmt(std::shared_ptr<Expr> expression) : expression(expression) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitExpressionStmt(*this);
    }
};

/*
* PrintStmt class that contains the functions to create a printstmt expression
* 
* Variables:
* expression: is a shared pointer to an Expr that contains the expression
* 
* Functions:
* PrintStmt: Constructor that creates a printstmt expression with the expression, 
* accept: Function to accept the visitor using the visitor pattern
*/
class PrintStmt : public Stmt {
public:
    std::shared_ptr<Expr> expression;

    PrintStmt(std::shared_ptr<Expr> expression) : expression(expression) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitPrintStmt(*this);
    }
};

/*
* VarStmt class that contains the functions to create a varstmt expression
* 
* Variables:
* name: is a Token that contains the name
* initializer: is a shared pointer to an Expr that contains the initializer
* 
* Functions:
* VarStmt: Constructor that creates a varstmt expression with the name, and initializer
* accept: Function to accept the visitor using the visitor pattern
*/
class VarStmt : public Stmt {
public:
    Token name;
    std::shared_ptr<Expr> initializer;

    VarStmt(Token name, std::shared_ptr<Expr> initializer) : name(name), initializer(initializer) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitVarStmt(*this);
    }
};

