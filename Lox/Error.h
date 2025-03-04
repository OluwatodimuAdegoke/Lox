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

/*
* Error class that contains the functions to report errors, runtime errors, and check if there were any errors
* Variables:
* hadError: is a boolean that checks if there were any errors and cancels the program if there were
* hadRuntimeError: is a boolean that checks if there were any runtime errors and cancels the program if there were

* Functions:
* report: Function to report the error and where it happened
* error: Function to report the error and where it happened using the report function


*/
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


class Return : public std::exception {
public:
	std::shared_ptr<Object> value;
	Return(std::shared_ptr<Object> value) : value(value) {};

};