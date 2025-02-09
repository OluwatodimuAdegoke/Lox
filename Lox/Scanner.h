#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.h"    
#include "Error.h"

class Scanner {
private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;
    static const std::unordered_map<std::string, TokenType> keywords;

    bool isAtEnd();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, std::shared_ptr<Object> literal);
	bool match(char expected);
	char peek();
	char peekNext();
    void string();
	bool isDigit(char c);
	void number();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	void identifier();
	void scanToken();
	void comment();
public:
	Scanner(const std::string& source) : source(source) {}
	std::vector<Token> scanTokens();
};

