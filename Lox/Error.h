#pragma once

#include <string>
#include "Token.h"  

class RuntimeError : public std::runtime_error {
public:
    std::shared_ptr<Token> token;

    RuntimeError(std::shared_ptr<Token> token, const std::string& message)
        : std::runtime_error(message), token(token) {}
};

class ParseError : public std::runtime_error {
public:
    ParseError(const std::string& message)
        : std::runtime_error(message) {}
};

class Error {
private:
    static void report(int line, const std::string& where, const std::string& message);

public:
    static bool hadError;
    static bool hadRuntimeError;

    static void error(int line, const std::string& message);
    static void error(const Token& token, const std::string& message);
    static void runtimeError(const RuntimeError& error);
};
