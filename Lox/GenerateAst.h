#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>


/*
* GenerateAst class that contains the functions to generate the AST classes and the visitor class
*/
class GenerateAst
{
public:
	static void defineAst(std::string outputDir, std::string baseName, std::vector<std::string> types);
	static void defineType(std::ofstream& file, std::string baseName, std::string className, std::string fieldList);
	static void defineVisitor(std::ofstream& file, std::string baseName, std::vector<std::string> types);
	static std::string toLowerCase(std::string& str);
};

