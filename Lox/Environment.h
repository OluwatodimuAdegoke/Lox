#pragma once
#include <map>
#include <iostream>
#include "Token.h"
#include "Object.h"
#include "Error.h"

class Environment : public std::enable_shared_from_this<Environment>
{
private:
    std::map<std::string, std::shared_ptr<Object>> values;
public:
    std::shared_ptr<Environment> enclosing;

    Environment();
    Environment(std::shared_ptr<Environment> enclosing);

    void define(const std::string& name, std::shared_ptr<Object> value);
    std::shared_ptr<Object> get(std::shared_ptr<Token> name);
    void assign(std::shared_ptr<Token> name, std::shared_ptr<Object> value);
	std::shared_ptr<Object> getAt(int distance, const std::string& name);
	void assignAt(int distance, const Token& name, std::shared_ptr<Object> value);
	std::shared_ptr<Environment> ancestor(int distance);
};