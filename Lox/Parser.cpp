#include "Parser.h"

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
	std::vector<std::shared_ptr<Stmt>> statements;
	while (!isAtEnd()) {
		statements.push_back(declaration());
	}
	return statements;
}

std::shared_ptr<Stmt> Parser::declaration() {
	try {
		if (match({ TokenType::CLASS })) return classDeclaration();
		if (match({ TokenType::FUN })) return functionStatement("function");
		if (match({ TokenType::VAR })) return varDeclaration();
		return statement();
	}
	catch (ParseError error) {
		synchronize();
		return nullptr;
	}
}

std::shared_ptr<Stmt> Parser::classDeclaration() {
	Token name = consume(TokenType::IDENTIFIER, "Expect class name.");

	std::shared_ptr<Variable> superclass = nullptr;
	if (match({ TokenType::LESS })) {
		consume(TokenType::IDENTIFIER, "Expect superclass name.");
		superclass = std::make_shared<Variable>(previous());
	}

	consume(TokenType::LEFT_BRACE, "Expect '{' before class body.");

	std::shared_ptr<std::vector<std::shared_ptr<FunctionStmt>>> methods = std::make_shared<std::vector<std::shared_ptr<FunctionStmt>>>();


	while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
		methods->push_back(std::dynamic_pointer_cast<FunctionStmt>(functionStatement("method")));
	}
	consume(TokenType::RIGHT_BRACE, "Expect '}' after class body.");

	return std::make_shared<ClassStmt>(name, superclass, methods);
}

std::shared_ptr<Stmt> Parser::functionStatement(const std::string& kind) {
	Token name = consume(TokenType::IDENTIFIER, "Expect " + kind + " name.");
	consume(TokenType::LEFT_PAREN, "Expect '(' after " + kind + " name.");

	std::shared_ptr<std::vector<Token>> parameters = std::make_shared<std::vector<Token>>();
	if (!check(TokenType::RIGHT_PAREN)) {
		do {
			if (parameters->size() >= 255) {
				error(peek(), "Cannot have more than 255 parameters.");
			}
			parameters->push_back(consume(TokenType::IDENTIFIER, "Expect parameter name."));
		} while (match({ TokenType::COMMA }));
	}
	consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");

	consume(TokenType::LEFT_BRACE, "Expect '{' before " + kind + " body.");
	std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> body = block();
	return std::make_shared<FunctionStmt>(name, parameters, body);
}

std::shared_ptr<Stmt> Parser::varDeclaration() {
	Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
	
	std::shared_ptr<Expr> initializer = nullptr;
	if (match({ TokenType::EQUAL })) {
		initializer = expression();
	}
	consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
	return std::make_shared<VarStmt>(name, initializer);

}

// Takes care of all the statements
std::shared_ptr<Stmt> Parser::statement() {
	if (match({ TokenType::FOR })) return forStatement();
	if (match({ TokenType::IF })) return ifStatement();
	if (match({ TokenType::PRINT })) return printStatement();
	if (match({ TokenType::RETURN })) return returnStatement();
	if (match({ TokenType::WHILE })) return whileStatement();
	if (match({ TokenType::LEFT_BRACE })) return std::make_shared<Block>(block());
	return expressionStatement();
}

std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> Parser::block() {
	std::vector<std::shared_ptr<Stmt>> statements;
	while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
		statements.push_back(declaration());
	}
	consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
	return std::make_shared<std::vector<std::shared_ptr<Stmt>>>(statements);
}

std::shared_ptr<Stmt> Parser::ifStatement() {
	consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
	std::shared_ptr<Expr> condition = expression();
	consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition.");

	std::shared_ptr<Stmt> thenBranch = statement();
	std::shared_ptr<Stmt> elseBranch = nullptr;
	if (match({ TokenType::ELSE })) {
		elseBranch = statement();
	}

	return std::make_shared<IfStmt>(condition, thenBranch, elseBranch);
}

std::shared_ptr<Stmt> Parser::printStatement() {
	std::shared_ptr<Expr> value = expression();
	consume(TokenType::SEMICOLON, "Expect ';' after value.");
	return std::make_shared<PrintStmt>(value);
}

std::shared_ptr<Stmt> Parser::expressionStatement() {
	std::shared_ptr<Expr> expr = expression();
	consume(TokenType::SEMICOLON, "Expect ';' after expression.");
	return std::make_shared<ExpressionStmt>(expr);
}

std::shared_ptr<Stmt> Parser::whileStatement() {
	consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
	std::shared_ptr<Expr> condition = expression();
	consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");
	std::shared_ptr<Stmt> body = statement();
	return std::make_shared<WhileStmt>(condition, body);
}

std::shared_ptr<Stmt> Parser::returnStatement() {
	Token keyword = previous();
	std::shared_ptr<Expr> value = nullptr;
	if (!check(TokenType::SEMICOLON)) {
		value = expression();
	}
	consume(TokenType::SEMICOLON, "Expect ';' after return value.");
	return std::make_shared<ReturnStmt>(keyword, value);
}

std::shared_ptr<Stmt> Parser::forStatement() {
	consume(TokenType::LEFT_PAREN, "Expect '(' after 'for'.");

	std::shared_ptr<Stmt> initializer;
	if (match({ TokenType::SEMICOLON })) {
		initializer = nullptr;
	}
	else if (match({ TokenType::VAR })) {
		initializer = varDeclaration();
	}
	else {
		initializer = expressionStatement();
	}

	std::shared_ptr<Expr> condition = nullptr;
	if (!check(TokenType::SEMICOLON)) condition = expression();
	consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");

	std::shared_ptr<Expr> increment = nullptr;
	if (!check(TokenType::RIGHT_PAREN)) increment = expression();
	consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");

	std::shared_ptr<Stmt> body = statement();
	
	if (increment != nullptr) {
		body = std::make_shared<Block>(std::make_shared<std::vector<std::shared_ptr<Stmt>>>(
			std::vector<std::shared_ptr<Stmt>>{
			body,
				std::make_shared<ExpressionStmt>(increment)
		}
		));
	}

	if (condition == nullptr) condition = std::make_shared<Literal>(std::make_shared<Bool>(true));
	body = std::make_shared<WhileStmt>(condition, body);

	if (initializer != nullptr) {
		body = std::make_shared<Block>(std::make_shared<std::vector<std::shared_ptr<Stmt>>>(
			std::vector<std::shared_ptr<Stmt>>{
			initializer,
				body
		}
		));
	}
	return body;
}

std::shared_ptr<Expr> Parser::expression() {
	return assignment();
}

std::shared_ptr<Expr> Parser::assignment() {
	std::shared_ptr<Expr> expr = orExpr();

	if (match({ TokenType::EQUAL })) {
		Token equals = previous();
		std::shared_ptr<Expr> value = assignment();

		if (std::dynamic_pointer_cast<Variable>(expr)) {
			Token name = std::dynamic_pointer_cast<Variable>(expr)->name;
			return std::make_shared<Assign>(name, value);
		}
		else if (std::dynamic_pointer_cast<Get>(expr)) {
			std::shared_ptr<Get> get = std::dynamic_pointer_cast<Get>(expr);
			return std::make_shared<Set>(get->object, get->name, value);
		}

		error(equals, "Invalid assignment target.");
	}
	return expr;
}

std::shared_ptr<Expr> Parser::orExpr() {
	std::shared_ptr<Expr> expr = andExpr();

	while (match({ TokenType::OR })) {
		Token op = previous();
		std::shared_ptr<Expr> right = andExpr();
		expr = std::make_shared<Logical>(expr, op, right);
	}
	return expr;
}

std::shared_ptr<Expr> Parser::andExpr() {
	std::shared_ptr<Expr> expr = equality();

	while (match({ TokenType::AND })) {
		Token op = previous();
		std::shared_ptr<Expr> right = equality();
		expr = std::make_shared<Logical>(expr, op, right);
	}
	return expr;
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
	return call();
}

std::shared_ptr<Expr> Parser::call() {
	std::shared_ptr<Expr> expr = primary();

	while (true) {
		if (match({ TokenType::LEFT_PAREN })) {
			expr = finishCall(expr);
		}
		else if (match({ TokenType::DOT })) {
			Token name = consume(TokenType::IDENTIFIER, "Expect property name after '.'.");
			expr = std::make_shared<Get>(expr, name);
		}
		else {
			break;
		}
	}

	return expr;
}

std::shared_ptr<Expr> Parser::finishCall(std::shared_ptr<Expr> callee) {
	std::vector<std::shared_ptr<Expr>> arguments;
	if (!check(TokenType::RIGHT_PAREN)) {
		do {
			if (arguments.size() >= 255) {
				error(peek(), "Cannot have more than 255 arguments.");
			}
			arguments.push_back(expression());
		} while (match({ TokenType::COMMA }));
	}

	Token paren = consume(TokenType::RIGHT_PAREN, "Expect ')' after arguments.");
	return std::make_shared<Call>(callee, paren, std::make_shared<std::vector<std::shared_ptr<Expr>>>(arguments));
}

std::shared_ptr<Expr> Parser::primary() {
	if (match({ TokenType::FALSE })) return std::make_shared<Literal>(std::make_shared<Bool>(false));
	if (match({ TokenType::TRUE }))  return std::make_shared<Literal>(std::make_shared<Bool>(true));
	if (match({ TokenType::NIL }))   return std::make_shared<Literal>(nullptr);

	if (match({ TokenType::NUMBER, TokenType::STRING })) {
		return std::make_shared<Literal>(previous().literal);
	}

	if (match({ TokenType::SUPER })) {
		Token keyword = previous();
		consume(TokenType::DOT, "Expect '.' after 'super'.");
		Token method = consume(TokenType::IDENTIFIER, "Expect superclass method name.");
		return std::make_shared<Super>(keyword, method);
	}

	if (match({ TokenType::THIS })) {
		auto thisExpr = std::make_shared<This>(previous());
		return thisExpr;

	}

	if (match({ TokenType::IDENTIFIER })) {
		return std::make_shared<Variable>(previous());
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

ParseError Parser::error(Token token,const std::string& message) {
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