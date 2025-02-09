#include "Token.h"

Token::Token(TokenType type, std::string lexeme,
    std::shared_ptr<Object> literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {
}

std::string Token::toString() const{
    std::string literalStr;
    return TokenTypeToString(type) + " " + lexeme + " " + literal->toString();
}



std::ostream& operator<<(std::ostream& out, const Token& token) {
    out << TokenTypeToString(token.type) << " " << token.lexeme << " " << token.literal->toString();
    return out;
}