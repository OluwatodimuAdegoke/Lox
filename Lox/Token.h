#pragma once

#include <string>
#include <iostream>
#include <ostream>
#include "Object.h"
#include "TokenType.h"


/*
* Token class that contains the functions to create a token and convert it to a string
* 
* Variables:
* type: is a TokenType that contains the type of the token
* lexeme: is a string that contains the lexeme of the token
* literal: is a shared pointer to an Object that contains the literal of the token
* line: is an integer that contains the line where the token is
* 
* Functions:
* Token: Constructor that creates a token with the type, lexeme, literal, and line
* toString: Function to convert the token to a string
* 
* Operators:
* operator<<: Overloads the << operator to print the token
*/

class Token {
public:
    TokenType type;
    std::string lexeme;
    std::shared_ptr<Object> literal;
    int line;

    Token(TokenType type, std::string lexeme,
        std::shared_ptr<Object> literal, int line);

	static std::string TokenTypeToString(TokenType type);
    std::string toString() const;
};

std::ostream& operator<<(std::ostream& out, const Token& token);