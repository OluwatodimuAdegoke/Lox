#pragma once
#include <vector>
#include "Token.h"
#include "Expr.h"
#include "Error.h"
#include "Stmt.h"

/*
* Parser class that contains the functions to parse the tokens
* It takes a vector of tokens and parses them into an expression
* 
* Variables:
* tokens: is a vector of tokens that contains the tokens to parse
* current: is an integer that contains the current token
* 
* 
* Functions:
* Parser: Constructor that creates a parser with the tokens
* expression: Function to parse the expression starting with the lowest precedence
* equality: Function to parse the equality expression 
* comparison: Function to parse the comparison expression
* term: Function to parse the term expression
* factor: Function to parse the factor expression
* unary: Function to parse the unary expression
* primary: Function to parse the primary expression
* 
* Helper Functions:
* match: Function to check if the current token matches the different types
* check: Function to check if the current token matches the type given
* advance: Function to advance the current token
* peek: Function to peek at the current token
* previous: Function to get the previous token
* isAtEnd: Function to check if the current token is at the end
* consume: Function to consume the current token
* error: Function to report the error and where it happened
* synchronize: Function to synchronize the parser
* 
*/
class Parser
{
private:

	std::vector<Token>& tokens;
	int current = 0;
	bool match(std::initializer_list<TokenType> types);
	bool check(TokenType type);
	Token advance();
	Token peek();
	Token previous();
	bool isAtEnd();

	Token consume(TokenType type,const std::string& message);
	ParseError error(Token token,const std::string& message);
	void synchronize();

	
	std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> block();
	std::shared_ptr<Expr> expression();
	std::shared_ptr<Expr> assignment();
	std::shared_ptr<Expr> equality();
	std::shared_ptr<Expr> comparison();
	std::shared_ptr<Expr> term();
	std::shared_ptr<Expr> factor();
	std::shared_ptr<Expr> unary();
	std::shared_ptr<Expr> primary();

	std::shared_ptr<Stmt> declaration();
	std::shared_ptr<Stmt> varDeclaration();
	std::shared_ptr<Stmt> statement();
	std::shared_ptr<Stmt> printStatement();
	std::shared_ptr<Stmt> expressionStatement();
public:
	Parser(std::vector<Token>& tokens) : tokens(tokens) {}
	std::vector<std::shared_ptr<Stmt>> parse();
};

