#pragma once

#include <string>
#include <iostream>
#include <ostream>
#include "Object.h"
#include "TokenType.h"


class Token {
public:
    TokenType type;
    std::string lexeme;
    std::shared_ptr<Object> literal;
    int line;

    Token(TokenType type, std::string lexeme,
        std::shared_ptr<Object> literal, int line);


    std::string toString() const;
};

std::ostream& operator<<(std::ostream& out, const Token& token);