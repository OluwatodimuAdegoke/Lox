#include "Error.h"

void Error::report(int line, std::string where, std::string message) {
	std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
	hadError = true;
}

void Error::error(int line, std::string message) {
	report(line, "", message);
}

void Error::error(Token token, std::string message) {
	if (token.type == TokenType::EOF_TOKEN) {
		report(token.line, " at end", message);
	}
	else {
		report(token.line, " at '" + token.lexeme + "'", message);
	}
}