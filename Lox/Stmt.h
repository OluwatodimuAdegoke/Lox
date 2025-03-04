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
* FunctionStmt class that contains the functions to create a functionstmt expression
* 
* Variables:
* name: is a Token that contains the name
* params: is a shared pointer to an std::vector<Token> that contains the params
* body: is a shared pointer to an std::vector<std::shared_ptr<Stmt>> that contains the body
* 
* Functions:
* FunctionStmt: Constructor that creates a functionstmt expression with the name, params, and body
* accept: Function to accept the visitor using the visitor pattern
*/
class FunctionStmt : public Stmt {
public:
    Token name;
    std::shared_ptr<std::vector<Token>> params;
    std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> body;

    FunctionStmt(Token name, std::shared_ptr<std::vector<Token>> params, std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> body) : name(name), params(params), body(body) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitFunctionStmt(*this);
    }
};

/*
* IfStmt class that contains the functions to create a ifstmt expression
* 
* Variables:
* condition: is a shared pointer to an Expr that contains the condition
* thenBranch: is a shared pointer to an Stmt that contains the thenBranch
* elseBranch: is a shared pointer to an Stmt that contains the elseBranch
* 
* Functions:
* IfStmt: Constructor that creates a ifstmt expression with the condition, thenBranch, and elseBranch
* accept: Function to accept the visitor using the visitor pattern
*/
class IfStmt : public Stmt {
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> thenBranch;
    std::shared_ptr<Stmt> elseBranch;

    IfStmt(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> thenBranch, std::shared_ptr<Stmt> elseBranch) : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitIfStmt(*this);
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
* ReturnStmt class that contains the functions to create a returnstmt expression
* 
* Variables:
* keyword: is a Token that contains the keyword
* value: is a shared pointer to an Expr that contains the value
* 
* Functions:
* ReturnStmt: Constructor that creates a returnstmt expression with the keyword, and value
* accept: Function to accept the visitor using the visitor pattern
*/
class ReturnStmt : public Stmt {
public:
    Token keyword;
    std::shared_ptr<Expr> value;

    ReturnStmt(Token keyword, std::shared_ptr<Expr> value) : keyword(keyword), value(value) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitReturnStmt(*this);
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

/*
* WhileStmt class that contains the functions to create a whilestmt expression
* 
* Variables:
* condition: is a shared pointer to an Expr that contains the condition
* body: is a shared pointer to an Stmt that contains the body
* 
* Functions:
* WhileStmt: Constructor that creates a whilestmt expression with the condition, and body
* accept: Function to accept the visitor using the visitor pattern
*/
class WhileStmt : public Stmt {
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> body;

    WhileStmt(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body) : condition(condition), body(body) {}

    void accept(VisitorStmt& visitor) override {
        visitor.visitWhileStmt(*this);
    }
};

