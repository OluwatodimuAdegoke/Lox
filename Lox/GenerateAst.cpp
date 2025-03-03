#include "GenerateAst.h"
#include <algorithm>
#include <sstream>
#include <iostream>

std::string GenerateAst::toLowerCase(std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

void GenerateAst::defineAst(std::string outputDir, std::string baseName, std::vector<std::string> types) {
    std::string path = outputDir + "/" + baseName + ".h";
    std::ofstream file(path);

    std::cout << "Generating " << path << std::endl;

    // Write header
    file << "#pragma once\n\n";
    file << "#include <vector>\n";
    file << "#include <memory>\n";
    file << "#include \"Token.h\"\n";
    file << "#include \"Object.h\"\n";
    file << "#include \"Visitor.h\"\n\n";

    if (baseName == "Stmt") {
        file << "#include \"Expr.h\"\n";
    }

    // Write base class documentation and definition
    file << "/*\n";
    file << "* " << baseName << " abstract class that contains the functions to accept the visitor\n";
    file << "* \n";
    file << "* Function:\n";
    file << "* accept: Function to accept the visitor using the visitor pattern\n";
    file << "*/\n";

    file << "class " << baseName << " {\n";
    file << "public:\n";
    file << "    virtual ~" << baseName << "() = default;\n";
	if (baseName == "Stmt") {
		file << "    virtual void accept(Visitor";
	}
	else {
    file << "    virtual std::shared_ptr<Object> accept(Visitor";
	}
    file << baseName;
    file << "& visitor) = 0;\n";
    file << "};\n\n";

    // Define each type
    for (std::string type : types) {
        std::string className = type.substr(0, type.find(":") - 1);
        std::string fields = type.substr(type.find(":") + 1);

        className.erase(className.find_last_not_of(" ") + 1);
        fields.erase(fields.find_last_not_of(" ") + 1);

        defineType(file, baseName, className, fields);
    }

    file.close();
}

void GenerateAst::defineType(std::ofstream& file, std::string baseName, std::string className, std::string fieldList) {
    // Write class documentation
    file << "/*\n";
    file << "* " << className << " class that contains the functions to create a " << toLowerCase(className) << " expression\n";
    file << "* \n";
    file << "* Variables:\n";

    // Parse fields
    std::vector<std::pair<std::string, std::string>> fields;
    std::stringstream ss(fieldList);
    std::string field;
    while (std::getline(ss, field, ',')) {
        std::istringstream iss(field);
        std::string type, name;
        iss >> type >> name;

        // Document each field
        file << "* " << name << ": is a ";
        if (type != "Token") {
            file << "shared pointer to an ";
        }
        file << type << " that contains the " << name << "\n";

        fields.push_back(std::make_pair(type, name));
    }

    file << "* \n";
    file << "* Functions:\n";
    file << "* " << className << ": Constructor that creates a " << toLowerCase(className) << " expression";
    if (!fields.empty()) {
        file << " with the ";
        for (size_t i = 0; i < fields.size(); i++) {
            file << fields[i].second;
            if (i < fields.size() - 2) file << ", ";
            else if (i == fields.size() - 2) file << ", and ";
        }
    }
    file << "\n";
    file << "* accept: Function to accept the visitor using the visitor pattern\n";
    file << "*/\n";

    // Class definition
    file << "class " << className << " : public " << baseName << " {\n";
    file << "public:\n";

    // Member variables
    for (const auto& field : fields) {
        std::string type = field.first;
        std::string name = field.second;
        if (type == "any") {
            type = "Object";
        }
        if (type != "Token") {
            file << "    std::shared_ptr<" << type << "> " << name << ";\n";
        }
        else {
            file << "    " << type << " " << name << ";\n";
        }
    }
    file << "\n";

    // Constructor
    file << "    " << className << "(";
    for (size_t i = 0; i < fields.size(); i++) {
        std::string type = fields[i].first;
        std::string name = fields[i].second;
        if (type == "any") {
            type = "Object";
        }
        if (type != "Token") {
            file << "std::shared_ptr<" << type << "> " << name;
        }
        else {
            file << type << " " << name;
        }
        if (i < fields.size() - 1) file << ", ";
    }
    file << ") : ";

    // Member initializer list
    for (size_t i = 0; i < fields.size(); i++) {
        file << fields[i].second << "(" << fields[i].second << ")";
        if (i < fields.size() - 1) file << ", ";
    }
    file << " {}\n\n";

    // Accept method
	if (baseName == "Stmt") {
		file << "    void accept(Visitor";
		file << baseName;
		file << "& visitor) override {\n";
        file << "        visitor.visit" << className << "(*this);\n";
	}
	else {
		file << "    std::shared_ptr<Object> accept(Visitor";
		file << baseName;
		file << "& visitor) override {\n";
		file << "        return visitor.visit" << className << baseName << "(*this);\n";

	}
    file << "    }\n";
    file << "};\n\n";
}


