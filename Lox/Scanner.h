#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.h"    
#include "Error.h"

/*
* Scanner class that contains the functions to scan the tokens from the source code
* 
* Variables:
* source: is a string that contains the source code
* tokens: is a vector of tokens that contains all the tokens from the source code
* start: is an integer that contains the start of the token
* current: is an integer that contains the current position of the token
* line: is an integer that contains the line number of the token
* 
* Functions:
* Scanner: Constructor that initializes the source variable
* scanTokens: Function that scans the tokens from the source 
* code by checking each character with their respective token type 
* and adding them to the tokens vector
* 
* Helper Functions:
* isAtEnd: Function that checks if the current position is at the end of the source code
* advance: Function that returns the current character and increments the current position
* addToken: Function that adds a token to the tokens vector
* addToken: Function that adds a token to the tokens vector with a literal
* match: Function that checks if the current character matches the expected character
* peek: Function that returns the current character
* peekNext: Function that returns the next character
* string: Function that scans the string token
* isDigit: Function that checks if the character is a digit
* number: Function that scans the number token
* isAlpha: Function that checks if the character is an alphabet
* isAlphaNumeric: Function that checks if the character is an alphabet or a digit
* identifier: Function that scans the identifier token
* scanToken: Function that scans the token by checking the current character and calling the respective function
* comment: Function that scans the comment token
* 
*/
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

