#include "Parser.h"

std::shared_ptr<Expr> Parser::parse() {
	try {
		return expression();
	}
	catch (const ParseError&) {
		return nullptr;
	}
}

std::shared_ptr<Expr> Parser::expression() {
	return equality();
}

std::shared_ptr<Expr> Parser::equality() {
	std::shared_ptr<Expr> expr = comparison();

	while(match({TokenType::BANG_EQUAL , TokenType::EQUAL_EQUAL})){
		Token op = previous();
		std::shared_ptr<Expr> right = comparison();
		expr = std::make_shared<Binary>(expr, op, right);
	}
	return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
	std::shared_ptr<Expr> expr = term();

	while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL })) {
		Token op = previous();
		std::shared_ptr<Expr> right = term();
		expr = std::make_shared<Binary>(expr, op, right);
	}
	return expr;
}

std::shared_ptr<Expr> Parser::term() {
	std::shared_ptr<Expr> expr = factor();

	while (match({ TokenType::MINUS, TokenType::PLUS })) {
		Token op = previous();
		std::shared_ptr<Expr> right = factor();
		expr = std::make_shared<Binary>(expr, op, right);
	}
	return expr;
}

std::shared_ptr<Expr> Parser::factor() {
	std::shared_ptr<Expr> expr = unary();

	while (match({ TokenType::SLASH, TokenType::STAR })) {
		Token op = previous();
		std::shared_ptr<Expr> right = unary();
		expr = std::make_shared<Binary>(expr, op, right);
	}
	return expr;
}

std::shared_ptr<Expr> Parser::unary() {
	if (match({ TokenType::BANG, TokenType::MINUS })) {
		Token op = previous();
		std::shared_ptr<Expr> right = unary();
		return std::make_shared<Unary>(op, right);
	}
	return primary();
}

std::shared_ptr<Expr> Parser::primary() {
	if (match({ TokenType::FALSE })) return std::make_shared<Literal>(std::make_shared<Bool>(false));
	if (match({ TokenType::TRUE }))  return std::make_shared<Literal>(std::make_shared<Bool>(true));
	if (match({ TokenType::NIL }))   return std::make_shared<Literal>(std::make_shared<Nil>());

	if (match({ TokenType::NUMBER, TokenType::STRING })) {
		return std::make_shared<Literal>(previous().literal);
	}

	if (match({ TokenType::LEFT_PAREN })) {
		auto expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_shared<Grouping>(expr);
	}

	throw error(peek(), "Expect expression.");
}


Token Parser::consume(TokenType type,const std::string& message) {
	if (check(type)) return advance();

	throw error(peek(), message);
}

Parser::ParseError Parser::error(Token token,const std::string& message) {
	Error::error(token, message);
	return ParseError("Parse error at '" + token.lexeme + "': " + message);
}

bool Parser::match(std::initializer_list<TokenType> types) {
	for (const TokenType& type : types) {
		if (check(type)) {
			advance();
			return true;
		}
	}
	return false;
}

bool Parser::check(TokenType type) {
	if (isAtEnd()) return false;
	return peek().type == type;
}

Token Parser::advance() {
	if (!isAtEnd()) current++;
	return previous();
}

Token Parser::peek() {
	return tokens[current];
}

Token Parser::previous() {
	return tokens[current - 1];
}

bool Parser::isAtEnd() {
	return peek().type == TokenType::EOF_TOKEN;
}

void Parser::synchronize() {
	advance();

	while (!isAtEnd()) {
		if (previous().type == TokenType::SEMICOLON) return;

		switch (peek().type) {
		case TokenType::CLASS:
		case TokenType::FUN:
		case TokenType::VAR:
		case TokenType::FOR:
		case TokenType::IF:
		case TokenType::WHILE:
		case TokenType::PRINT:
		case TokenType::RETURN:
			return;
		}
		advance();
	}
}