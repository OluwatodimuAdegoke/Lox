#pragma once
#include <vector>
#include "Token.h"
#include "Expr.h"
#include "Error.h"


class Parser
{
private:

	class ParseError : public std::runtime_error {
	public:
		ParseError(const std::string& message): std::runtime_error(message) {}
	};

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

	std::shared_ptr<Expr> expression();
	std::shared_ptr<Expr> equality();
	std::shared_ptr<Expr> comparison();
	std::shared_ptr<Expr> term();
	std::shared_ptr<Expr> factor();
	std::shared_ptr<Expr> unary();
	std::shared_ptr<Expr> primary();
public:
	Parser(std::vector<Token>& tokens) : tokens(tokens) {}
	std::shared_ptr<Expr> parse();
};

