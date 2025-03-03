#pragma once
#include <string>
#include <vector>
#include <fstream>

class GenerateAst {
public:
    // Convert a string to lowercase
    static std::string toLowerCase(std::string& str);

    // Define the AST classes in the output file
    static void defineAst(std::string outputDir, std::string baseName, std::vector<std::string> types);

private:
    // Define a single type/class in the AST
    static void defineType(std::ofstream& file, std::string baseName, std::string className, std::string fieldList);
};