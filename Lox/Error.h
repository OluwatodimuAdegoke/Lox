#pragma once

#include <string>
#include <iostream>
#include "Token.h"

class Error {
private:
	static void report(int line, std::string where, std::string message);
public:
	static bool hadError;
	static void error(int line, std::string message);
	static void error(Token token, std::string message);
};