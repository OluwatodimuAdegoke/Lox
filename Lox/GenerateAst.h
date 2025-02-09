#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

class GenerateAst
{
public:
	static void defineAst(std::string outputDir, std::string baseName, std::vector<std::string> types);
	static void defineType(std::ofstream& file, std::string baseName, std::string className, std::string fieldList);
	static void defineVisitor(std::ofstream& file, std::string baseName, std::vector<std::string> types);
	static std::string toLowerCase(std::string& str);
};

