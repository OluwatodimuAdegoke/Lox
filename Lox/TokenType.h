#pragma once

#include <string>

// Represents the different types of tokens that the scanner can return.
enum TokenType {
	//Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	//One or two character tokens.
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

	//Lietrals.
	IDENTIFIER, STRING, NUMBER,

	//Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	EOF_TOKEN,
};

// Converts the TokenType to a string.
std::string TokenTypeToString(TokenType type);