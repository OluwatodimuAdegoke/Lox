#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Token.h"
#include "Error.h"
#include "Scanner.h"
#include "Parser.h"
#include "AstPrinter.h"
#include "Interpreter.h"

/*
* Lox class that contains the main functions to run the file, prompt, and connect the source code to the scanner, parser, and interpreter
*
* Variables:
* interpreter: static instance of the Interpreter class used to interpret expressions
*
* Functions:
* runFile: Function to run the file directly
* runPrompt: Function to run the prompt for the user where you can execute code line by line
* run: Function to connect the source code to the scanner, parser, and interpreter
*
*/

class Lox {
private:
    static std::shared_ptr<Interpreter> interpreter;

public:
    // Run Lox code from a file
    static void runFile(const char* path);

    // Run Lox code from an interactive prompt
    static void runPrompt();

    // Execute a string of Lox source code
    static void run(std::string source);
};