// Lox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Error.h"
#include "Scanner.h"
#include "Parser.h"
#include "AstPrinter.h"
#include "Interpreter.h"


/*
*Lox class that contains the main functions to run the file, prompt, and connect the source code to the scanner, parser, and interpreter
* Variables:
* 
* Functions:
* runFile: Function to run the file directly
* runPrompt: Function to run the prompt for the user where you can execute code line by line
* run: Function to connect the source code to the scanner, parser, and interpreter
* 
*/
class Lox {
private:
	static Interpreter interpreter;

public:

	static void runFile(const char* path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cout << "Could not open file:  " << path << std::endl;
			exit(65);
		}

		std::string line, content;
		while (std::getline(file, line)) {
			content += line + "\n";
		}
		file.close();

		run(content);

		// Indicate an error in the exit code.
		if (Error::hadError) exit(65);
		if (Error::hadRuntimeError) exit(70);
	}


	static void runPrompt() {
		std::string line;

		while (true) {
			std::cout << "> ";
			std::getline(std::cin, line);
			if (line.empty()) break;
			run(line);
			Error::hadError = false;
		}
	}

	
	static void run(std::string source) {
		Scanner scanner(source);
		std::vector<Token> tokens = scanner.scanTokens();
		
		Parser parser(tokens);
		std::shared_ptr<Expr> expression = parser.parse();

		if (Error::hadError) return;

		interpreter.interpret(expression);

	}
	



};

// Intialize the static variable
bool Error::hadError = false;
bool Error::hadRuntimeError = false;
Interpreter Lox::interpreter;


// Main function that handles the command line arguments
int main(int argc, char *argv[])
{

	// If there are more than 2 arguments, print usage
	if (argc > 2) {
		std::cout << "Usage: lox [script]";
		return 64;
	}
	//If there is two arguments, run the file
	else if (argc == 2) {
		Lox::runFile(argv[1]);
	}
	// If there is only one argument, run the prompt
	else {
		Lox::runPrompt();
	}
};
