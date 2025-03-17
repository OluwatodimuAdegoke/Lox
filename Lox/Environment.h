#pragma once
#include <map>
#include <iostream>
#include "Token.h"
#include "Object.h"
#include "Error.h"

class Environment
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
};