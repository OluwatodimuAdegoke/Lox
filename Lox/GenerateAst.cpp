#include "GenerateAst.h"


std::string GenerateAst::toLowerCase(std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) {return std::tolower(c);});
	return lowerStr;
}
void GenerateAst::defineAst(std::string outputDir, std::string baseName, std::vector<std::string> types) {
	std::string path = outputDir + baseName + ".h";
	std::ofstream file(path);

	std::cout << "Generating " << path << std::endl;
	file << "#pragma once\n";
	file << "\n";
	file << "#include <vector>\n";
	file << "#include <memory>\n";
	file << "#include <variant>\n";
	file << "#include " << "\"Token.h\"\n";
	file << "\n";

	file << "class " << baseName << " {\n";
	file << "public:\n";
	file << "	virtual ~" << baseName << "() = default;\n";
	file << "	template <typename R>\n";
	file << "	R accept(Visitor<R>& visitor);\n";
	file << "};";
		
	file << "\n";
	file << "\n";



	for (std::string type : types) {
		std::string className = type.substr(0, type.find(":") - 1);
		std::string fields = type.substr(type.find(":") + 1);

		className.erase(className.find_last_not_of(" ") + 1);
		fields.erase(fields.find_last_not_of(" ") + 1);

		defineType(file, baseName, className, fields);
	}
	defineVisitor(file, baseName, types);
	file.close();
}

void GenerateAst::defineVisitor(std::ofstream& file, std::string baseName, std::vector<std::string> types) {

	file << "template <typename R>\n";
	file << "class Visitor {\n";
	file << "public:\n";
	file << "	virtual ~" << "Visitor() = default;\n";
	for (std::string type : types) {
		std::string typeName = type.substr(0, type.find(":") - 1);
		typeName.erase(typeName.find_last_not_of(" ") + 1);
		file << "	virtual R visit" << typeName << baseName << "(" <<"const " << typeName << "& " << GenerateAst::toLowerCase(baseName) << ") = 0; \n";
	}
	file << "};";
	file << "\n";
}

void GenerateAst::defineType(std::ofstream& file, std::string baseName, std::string className, std::string fieldList) {
	file << "\n";
	file << "class " << className << " : public " << baseName << " {\n";
	file << "public:\n";
	file << "\n";
	std::vector<std::pair<std::string, std::string>> fields;
	std::stringstream iss(fieldList);
	std::string field;
	while (std::getline(iss, field, ',')) {
		std::istringstream iss(field);
		std::string type, name;
		iss >> type >> name;
		fields.push_back(make_pair(type, name));
	}

	for (std::pair<std::string, std::string> field : fields) {
		std::string type = field.first;
		std::string name = field.second;
		if (type == "any") {
			 type = "std::variant<std::nullptr_t, double, std::string>";
		}
		if (type != "Token") {
			file << "	" << "std::shared_ptr<" << type << "> " << name << ";\n";
		}
		else {
			file << "    " << type << " " << name << ";\n";
		}
	}


	file << "\n";


	file << "	" << className << "(";
	for (int i = 0; i < fields.size(); i++) {
		std::string type = fields[i].first;
		std::string name = fields[i].second;
		if (type == "any") {
			type = "std::variant<std::nullptr_t, double, std::string>";
		}
		if (type != "Token") {
			file << "std::shared_ptr<" << type << "> " << name;
		}
		else {
			file << type << " " << name;
		}
		if (i != fields.size() - 1) {
			file << ", ";
		}
	}
	file << ") : ";
	for (int i = 0; i < fields.size(); i++) {
		std::string type = fields[i].first;
		std::string name = fields[i].second;
		if (type == "any") {
			type = "std::variant<std::nullptr_t, double, std::string>";
		}
		if (type != "Token") {
			file << name << "(" << name << ")";
		}
		else {
			file << name << "(" << name << ")";
		}
		if (i != fields.size() - 1) {
			file << ", ";
		}
	}
	file << " {}";
	file << "\n";
	file << "\n";
	file << "	template <typename R>\n";
	file << "	R accept(Visitor<R>& visitor){\n";
	file << "		return visitor.visit" << className << baseName << "(*this);\n";
	file << "	}\n";
	file << "\n";
	file << "};\n";



}


//int main(int argc, char* argv[])
//{
//	if (argc != 2) {
//		std::cout << "Usage: generate_ast <output directory>";
//		return 64;
//	}
//	std::string outputDir = argv[1];
//	GenerateAst::defineAst(outputDir, "Expr", {
//		"Binary   : Expr left, Token operators, Expr right",
//		"Grouping : Expr expression",
//		"Literal  : any value",
//		"Unary    : Token operators, Expr right"
//		});
//};
