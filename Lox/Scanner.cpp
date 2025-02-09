#include "Scanner.h"


bool Scanner::isAtEnd() {
	return current >= source.length();
}

char Scanner::advance() {
	return source[current++];
}

void Scanner::addToken(TokenType type) {
	addToken(type, std::make_shared<Nil>());
}

void Scanner::addToken(TokenType type, std::shared_ptr<Object> literal) {
	int length = current - start;
	std::string text = source.substr(start, length);
	tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
	if (isAtEnd()) return false;
	if (source[current] != expected) return false;
	current++;
	return true;
}

char Scanner::peek() {
	if (isAtEnd()) return '\0';
	return source[current];
}

char Scanner::peekNext() {
	if (current + 1 >= source.length()) return '\0';
	return source[current + 1];
}

void Scanner::string() {
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') line++;
		advance();
	}
	if (isAtEnd()) {
		Error::error(line, "Unterminated string.");
		return;
	}
	advance();
	int length = current - start - 2;
	String value = source.substr(start + 1, length);
	addToken(TokenType::STRING, std::make_shared<String>(value));
}

bool Scanner::isDigit(char c) {
	return c >= '0' && c <= '9';
}

void Scanner::number() {
	while (isDigit(peek())) advance();
	if (peek() == '.' && isDigit(peekNext())) {
		advance();
		while (isDigit(peek())) advance();
	}
	Number value = std::stod(source.substr(start, current - start));
	addToken(TokenType::NUMBER, std::make_shared<Number>(value));
}

bool Scanner::isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
	return isAlpha(c) || isDigit(c);
}

void Scanner::identifier() {
	while (isAlphaNumeric(peek())) advance();
	std::string text = source.substr(start, current - start);
	auto it = keywords.find(text);
	TokenType type;
	if (it == keywords.end()) {
		type = TokenType::IDENTIFIER;
	}
	else {
		type = it->second;
	}
	addToken(type);
}


void Scanner::comment() {
	if (match('/')) {
		while (peek() != '\n' && !isAtEnd()) advance();
	}
	else if (match('*')) {
		while (!isAtEnd()) {
			if (peek() == '*' && peekNext() == '/') {
				advance();
				advance();
				return;
			}
			if (peek() == '\n') line++; 
			advance();
		}

		Error::error(line, "Unterminated block comment.");
	}
	else {
		addToken(TokenType::SLASH); 
	}
}


void Scanner::scanToken() {
	char c = advance();
	switch (c) {
	case '(': addToken(TokenType::LEFT_PAREN); break;
	case ')': addToken(TokenType::RIGHT_PAREN); break;
	case '{': addToken(TokenType::LEFT_BRACE); break;
	case '}': addToken(TokenType::RIGHT_BRACE); break;
	case ',': addToken(TokenType::COMMA); break;
	case '.': addToken(TokenType::DOT); break;
	case '-': addToken(TokenType::MINUS); break;
	case '+': addToken(TokenType::PLUS); break;
	case ';': addToken(TokenType::SEMICOLON); break;
	case '*': addToken(TokenType::STAR); break;
	case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
	case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
	case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
	case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
	case '/':comment();break;
	case ' ':
	case '\r':
	case '\t':
		break;
	case '\n':
		line++;
		break;
	case '"': string(); break;
	default:
		if (isDigit(c)) {
			number();
		}
		else if (isAlpha(c)) {
			identifier();
		}
		else {
			Error::error(line, "Unexpected character.");
		}
		break;
	}
}

std::vector<Token> Scanner::scanTokens() {
	while (!isAtEnd()) {
		// We are at the beginning of the next lexeme.
		start = current;
		scanToken();
	}
	// Add EOF token at the end
	tokens.push_back(Token(TokenType::EOF_TOKEN, "", std::make_shared<Nil>(), line));
	return tokens;
}


const std::unordered_map<std::string, TokenType> Scanner::keywords = {
	{"and", TokenType::AND},
	{"class", TokenType::CLASS},
	{"else", TokenType::ELSE},
	{"false", TokenType::FALSE},
	{"for", TokenType::FOR},
	{"fun", TokenType::FUN},
	{"if", TokenType::IF},
	{"nil", TokenType::NIL},
	{"or", TokenType::OR},
	{"print", TokenType::PRINT},
	{"return", TokenType::RETURN},
	{"super", TokenType::SUPER},
	{"this", TokenType::THIS},
	{"true", TokenType::TRUE},
	{"var", TokenType::VAR},
	{"while", TokenType::WHILE}
};