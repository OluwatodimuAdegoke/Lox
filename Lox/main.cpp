#include "GenerateAst.h"
#include <iostream>
#include "Error.h"
#include "Lox.h"

//int main(int argc, char* argv[]) {
//    if (argc != 2) {
//        std::cout << "Usage: generate_ast <output directory>\n";
//        return 64;
//    }
//    std::string outputDir = "C:/Dev/C++/Lox/Lox";
//    GenerateAst::defineAst(outputDir, "Expr", {
//		"Assign   : Token name, Expr value",
//        "Binary   : Expr left, Token op, Expr right",
//		"Call     : Expr callee, Token paren, std::vector<std::shared_ptr<Expr>> arguments",
//        "Grouping : Expr expression",
//        "Literal  : Object value",
//        "Logical  : Expr left, Token op, Expr right",
//        "Unary    : Token op, Expr right",
//		"Variable : Token name"
//        });
//
//
//    GenerateAst::defineAst(outputDir, "Stmt", {
//	"Block : std::vector<std::shared_ptr<Stmt>> statements",
//    "ExpressionStmt   : Expr expression",
//	"FunctionStmt : Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmt>> body",
//    "IfStmt : Expr condition, Stmt thenBranch, Stmt elseBranch",
//    "PrintStmt : Expr expression",
//	"ReturnStmt : Token keyword, Expr value",
//	"VarStmt : Token name, Expr initializer",
//	"WhileStmt : Expr condition, Stmt body"
//        });
//
//
//    return 0;
//}



// Intialize the static variable
bool Error::hadError = false;
bool Error::hadRuntimeError = false;
Interpreter Lox::interpreter;


// Main function that handles the command line arguments
int main(int argc, char *argv[])
{

	argc = 1;
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
