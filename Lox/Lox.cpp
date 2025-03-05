#include "Lox.h"

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

	void Lox::runFile(const char* path) {
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


	void Lox::runPrompt() {
		std::string line;

		while (true) {
			std::cout << "> ";
			std::getline(std::cin, line);
			if (line.empty()) break;
			run(line);
			Error::hadError = false;
		}
	}

	
	void Lox::run(std::string source) {
		Scanner scanner(source);
		std::vector<Token> tokens = scanner.scanTokens();
		
		Parser parser(tokens);
		std::vector<std::shared_ptr<Stmt>> statements = parser.parse();

		if (Error::hadError) return;

		Resolver resolver = Resolver(std::make_shared<Interpreter>());
		resolver.resolve(std::make_shared<std::vector<std::shared_ptr<Stmt>>>(statements));


		if (Error::hadError) return;

		interpreter.interpret(statements);

	}
	


