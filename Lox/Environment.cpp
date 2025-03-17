#include "Environment.h"
#include <iostream>

Environment::Environment() {
	values = std::map<std::string, std::shared_ptr<Object>>();
	enclosing = nullptr;
}

Environment::Environment(std::shared_ptr<Environment> enclosing) {
	values = std::map<std::string, std::shared_ptr<Object>>();
	this->enclosing = enclosing;
}

void Environment::define(const std::string& name, std::shared_ptr<Object> value)
{
	values[name] = value;
}

std::shared_ptr<Object> Environment::get(std::shared_ptr<Token> name) {
	if (values.find(name->lexeme) != values.end()) {
		return values[name->lexeme];
	}
	if (enclosing != nullptr) return enclosing->get(name);

	throw RuntimeError(name, "Undefined variable '" + name->lexeme + "'.");
}


void Environment::assign(std::shared_ptr<Token> name, std::shared_ptr<Object> value) {
	if (values.find(name->lexeme) != values.end()) {
		values[name->lexeme] = value;
		return;
	}

	if (enclosing != nullptr) {
		enclosing->assign(name, value);
		return;
	}
	throw RuntimeError(name, "Undefined variable '" + name->lexeme + "'.");
}