#include "Error.h"

void Error::report(int line, const std::string& where, const std::string& message) {
    std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}

void Error::error(int line, const std::string& message) {
    report(line, "", message);
}

void Error::error(const Token& token, const std::string& message) {
    if (token.type == TokenType::EOF_TOKEN) {
        report(token.line, " at end", message);
    }
    else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void Error::runtimeError(const RuntimeError& error) {
    std::cout << error.what() << "\n[line " << error.token->line << "]" << std::endl;
    hadRuntimeError = true;
}
